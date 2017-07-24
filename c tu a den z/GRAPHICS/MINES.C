#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <dos.h>

int mouse_status;
int mouse_x;
int mouse_y;

int  mouse_reset(void);
void mouse_enable(void);
void mouse_disable(void);
void mouse_read_cursor(void);
void mouse_horizontal_range(int xmin, int xmax);
void mouse_vertical_range(int ymin, int ymax);

/*************************************************************************
*                                                                        *
*                           F U N C T I O N S                            *
*                                                                        *
*************************************************************************/

/*----------------------------------------------------------------------*/

int mouse_reset(void)
{
   _AX=0;
   geninterrupt(0x33);
   return(_AX);
}	/* mouse_reset */

/*----------------------------------------------------------------------*/

void mouse_enable(void)
{
   _AX=1;
   geninterrupt(0x33);
}	/* mouse_enable */


/*----------------------------------------------------------------------*/

void mouse_disable(void)
{
   _AX=2;
   geninterrupt(0x33);
}	/* mouse_disable */

/*----------------------------------------------------------------------*/

void mouse_read_cursor(void)
{
   _AX=3;
   geninterrupt(0x33);
   mouse_status=_BX;
   mouse_x=_CX;
   mouse_y=_DX;
}	/* mouse_read_cursor */

/*----------------------------------------------------------------------*/

void mouse_horizontal_range(int xmin, int xmax)
{
   _AX=7;
   _CX=xmin;
   _DX=xmax;
   geninterrupt(0x33);
}	/* mouse_vertical_range */

/*----------------------------------------------------------------------*/

void mouse_vertical_range(int ymin, int ymax)
{
   _AX=8;
   _CX=ymin;
   _DX=ymax;
   geninterrupt(0x33);
}	/* mouse_vertical_range */
#define YES 1
#define NO  0

#define XPX 15		/* X pixels by square */
#define YPX 15		/* Y pixels by square */

#define DEFCX 30	/* Default number of squares */
#define DEFCY 28

#define MINE 255-'0'	/* So that when it prints, it prints char 0xff */

#define STSQUARE struct stsquare

STSQUARE {
   unsigned char value;		/* Number of mines in the surround squares */
   unsigned char sqopen;	/* Square is open */
   unsigned char sqpress;	/* Square is pressed */
   unsigned char sqmark;	/* Square is marked */
} *psquare;

#define value(x,y)   (psquare+(x)*ncy+(y))->value
#define sqopen(x,y)  (psquare+(x)*ncy+(y))->sqopen
#define sqpress(x,y) (psquare+(x)*ncy+(y))->sqpress
#define sqmark(x,y)  (psquare+(x)*ncy+(y))->sqmark

int XST,	/* Offset of first pixel X */
    YST,
    ncx,	/* Number of squares in X */
    ncy,
    cmines,	/* Mines discovered */
    initmines,	/* Number of initial mines */
    sqclosed,	/* Squares still closed */
    maxy;	/* Max. number of y pixels of the screen */

void Graph_init(void);
void Read_param(int argc, char *argv[]);
void Set_mines(int nminas);
void Set_square(int x, int y, int status);
void Mouse_set(void);
void Draw_squares(void);
int  Do_all(void);
void Blow_up(void);
void Open_square(int x, int y);
int  Open_near_squares(int x, int y);

/************************************************************************/

void main(int argc, char *argv[])
{
   if (!mouse_reset()) {
      cputs(" ERROR: I can't find a mouse driver\r\n");
      exit(2);
   }
   Graph_init();
   Read_param(argc, argv);
   Mouse_set();
   do {
      randomize();
      cleardevice();
      Set_mines(cmines=initmines);
      mouse_enable();
      Draw_squares();
   }
   while (Do_all() != '\x1b');
   closegraph();
}

/*************************************************************************
*                                                                        *
*                           F U N C T I O N S                            *
*                                                                        *
*************************************************************************/

/*----------------------------------------------------------------------*/

void Graph_init(void)
{
   int graphdriver=DETECT, graphmode, errorcode;

      if(errorcode < 0) {
     cprintf("\n\rGraphics System Error: %s\n",grapherrormsg(errorcode));
     exit(98);
   }
   initgraph(&graphdriver, &graphmode, "");
   errorcode=graphresult();
   if(errorcode!=grOk) {
     printf(" Graphics System Error: %s\n",grapherrormsg(errorcode));
     exit(98);
   }
   maxy=getmaxy();
}	/* Graph_init */

/*----------------------------------------------------------------------*/

void Read_param(int argc, char *argv[])
{
   int x, y, m;

   x=y=m=0;
   if (argc!=1) {
      if (!isdigit(*argv[1])) {
	 closegraph();
	 cprintf("Usage is: %s [x] [y] [m]\r\n\n"
		 "Where x is the horizontal size\r\n"
		 "      y is the vertical size\r\n"
		 "      m is the number of mines\r\n\n"
		 " Left mouse button: Open the square\r\n"
		 "Right mouse button: Mark the square\r\n"
		 "                    -The first time puts a 'mine' mark\r\n"
		 "                    -The second time puts a 'possible "
                                     "mine' mark\r\n"
		 "                    -The third time unmarks the square\r\n"
		 "Left+Right buttons: Open the surrounded squares only if "
		                     "the count of mines\r\n"
                 "                     is equal to the number in the square",argv[0]);
	 exit (1);
      }
      switch (argc) {
	 case 4: m=atoi(argv[3]);
	 case 3: y=atoi(argv[2]);
	 case 2: x=atoi(argv[1]);
      }
   }
   XST=100;
   ncx=DEFCX;
   if (maxy==479) {
      YST=30;
      ncy=DEFCY;
   }
   else {
      YST=25;
      ncy=20;
   }
   if (x>0 && x<ncx)
      ncx=x;
   if (y>0 && y<ncy) {
      YST+=((ncy-y)*YPX)>>1;
      ncy=y;
   }
   initmines= m ? m : ncx*ncy*4/25;	/* There are about 16% of mines */
   if (((void near*)psquare=calloc(ncx*ncy, sizeof(STSQUARE)))==NULL) {
      closegraph();
      cputs("ERROR: Not enought memory");
      exit(3);
   }
}	/* Read_param */

/*----------------------------------------------------------------------*/

void Set_mines(int nminas)
{
   STSQUARE *p;
   int i, x, y, a, b;

   sqclosed=ncx*ncy-nminas;
   p=psquare;
   for (i=ncx*ncy; i>0; i--, p++)
      p->value = p->sqopen = p->sqpress = p->sqmark = NO;
   for (i=nminas; i>0; i--) {
      while (value(x=random(ncx), y=random(ncy)) == MINE)
	 ;
      value(x,y)=MINE;
   }
   for (x=ncx-1; x>=0; x--) {
      for (y=ncy-1; y>=0; y--) {
	 if (value(x,y) == MINE)
	    continue;
	 a=x-1;
	 b=y-1;
	 if (a>=0 && b>=0 && a<ncx && b<ncy)
	    value(x,y)+=(value(a,b) == MINE);
	 a++;
	 if (a>=0 && b>=0 && a<ncx && b<ncy)
	    value(x,y)+=(value(a,b) == MINE);
	 a++;
	 if (a>=0 && b>=0 && a<ncx && b<ncy)
	    value(x,y)+=(value(a,b) == MINE);
	 b++;
	 if (a>=0 && b>=0 && a<ncx && b<ncy)
	    value(x,y)+=(value(a,b) == MINE);
	 a-=2;
	 if (a>=0 && b>=0 && a<ncx && b<ncy)
	    value(x,y)+=(value(a,b) == MINE);
	 b++;
	 if (a>=0 && b>=0 && a<ncx && b<ncy)
	    value(x,y)+=(value(a,b) == MINE);
	 a++;
	 if (a>=0 && b>=0 && a<ncx && b<ncy)
	    value(x,y)+=(value(a,b) == MINE);
	 a++;
	 if (a>=0 && b>=0 && a<ncx && b<ncy)
	    value(x,y)+=(value(a,b) == MINE);
      }
   }
}	/* Set_mines */

/*----------------------------------------------------------------------*/

/*
   If status=1 then draw the square up, if it's 0 then draw it down
*/
void Set_square(int x, int y, int status)
{
   int xl, xr, yt, yb;

   mouse_disable();
   xl=XST+XPX*x;
   xr=xl+XPX-1;
   yt=YST+YPX*y;
   yb=yt+YPX-1;
   setfillstyle(SOLID_FILL, LIGHTGRAY);
   bar(xl, yt, xr, yb);
   if (status) {
      setcolor(WHITE);
      line(xl,yt,xl,yb-1);
      line(xl,yt,xr-1,yt);
      setcolor(DARKGRAY);
      line(xr,yb,xl,yb);
      line(xr,yb,xr,yt);
      switch (sqmark(x,y)) {
	 case 2 : setfillstyle(SOLID_FILL, LIGHTBLUE);
		  setcolor(LIGHTBLUE);
		  break;
	 case 1 : setfillstyle(SOLID_FILL, LIGHTRED);
		  setcolor(LIGHTRED);
		  break;
	 default: setcolor(LIGHTGRAY);
      }
      fillellipse(XST+XPX*x+XPX/2, YST+YPX*y+YPX/2, 3, 3);
      switch (sqmark(x,y)) {
	 case 2 :
	 case 1 : setfillstyle(SOLID_FILL, YELLOW);
		  setcolor(YELLOW);
		  fillellipse(XST+XPX*x+XPX/2, YST+YPX*y+YPX/2, 1, 1);
      }
   }
   else {
      sqclosed--;
      setcolor(DARKGRAY);
      line(xl,yt,xl,yb);
      line(xl,yt,xr,yt);
   }
   mouse_enable();
}	/* Set_square */

/*----------------------------------------------------------------------*/

void Mouse_set(void)
{
   mouse_horizontal_range(XST, XST+XPX*ncx-3);
   mouse_vertical_range(YST, YST+YPX*ncy-3);
}	/* Mouse_set */

/*----------------------------------------------------------------------*/

void Draw_squares(void)
{
   int x, y;

   mouse_disable();
   for (x=0; x<ncx; x++)
      for (y=0; y<ncy; y++)
	 Set_square(x,y,1);
   mouse_enable();
}	/* Draw_squares */

/*----------------------------------------------------------------------*/

/*
   Here we do all the job
*/
int Do_all(void)
{
   int x, y, xant=-1, yant, mlstant, mrstant, cminasant=0, ttrans, tant=0;
   long tst, tact;
   char str[] ="xxxxx: 0000",
	blk[] ="ллллллллллл";

   mouse_enable();
   time(&tst);
   while (!kbhit()) {
      if (!sqclosed && !mouse_status) {		/* All mines discovered */
	 settextjustify(LEFT_TEXT, CENTER_TEXT);
	 setcolor(BLACK);
	 outtextxy(0, maxy/2-10, blk);
	 sprintf(str,"Mines:    0");
	 setcolor(LIGHTRED);
	 outtextxy(0, maxy/2-10, str);
	 settextjustify(LEFT_TEXT, CENTER_TEXT);
	 setcolor(BLACK);
	 outtextxy(0, maxy/2+10, blk);
	 sprintf(str," Time: %4d",ttrans);
	 setcolor(LIGHTGREEN);
	 outtextxy(0, maxy/2+10, str);
	 for (x=ncx-1; x>=0; x--)
	    for (y=ncy-1; y>=0; y--)
	       if (value(x,y)==MINE) {
		  sqmark(x,y)=1;
		  Set_square(x,y,1);
	       }
	 break;
      }
      if (cminasant != cmines) {		/* Update Mines: */
	 cminasant=cmines;
	 settextjustify(LEFT_TEXT, CENTER_TEXT);
	 setcolor(BLACK);
	 outtextxy(0, maxy/2-10, blk);
	 sprintf(str,"Mines: %4d",cmines);
	 setcolor(LIGHTRED);
	 outtextxy(0, maxy/2-10, str);
      }
      if (tant != (ttrans=(int)(time(&tact)-tst))) {	/* Update Time: */
	 tant=ttrans;
	 settextjustify(LEFT_TEXT, CENTER_TEXT);
	 setcolor(BLACK);
	 outtextxy(0, maxy/2+10, blk);
	 sprintf(str," Time: %4d",ttrans);
	 setcolor(LIGHTRED);
	 outtextxy(0, maxy/2+10, str);
      }
      mouse_read_cursor();
      mouse_status&=3;
      x=(mouse_x-XST)/XPX;
      y=(mouse_y-YST)/YPX;
      if (xant == -1) {
	 xant=x;
	 yant=y;
      }
      if (x!=xant || y!=yant) {				/* Position change */
	 if (sqpress(xant,yant) && !sqopen(xant,yant)) {
	    sqpress(xant,yant)=NO;
	    Set_square(xant,yant,1);
	 }
	 xant=x;
	 yant=y;
      }
      if (!mouse_status)
	 mlstant=mrstant=0;
      if ((mouse_status == 2) &&
	   !sqopen(x,y)       &&
	   mlstant!=mouse_status) {	/* Right button pressed */
	 mlstant=mouse_status;
	 mouse_disable();
	 switch (sqmark(x,y)=(sqmark(x,y)+1) % 3) {
	    case 1 : cmines--; break;
	    case 2 : cmines++;
	 }
	 Set_square(x,y,1);
	 mouse_enable();
      }
      else if (mouse_status==1 &&	/* Left button pressed */
	       !sqopen(x,y)    &&
	       !sqpress(x,y)   &&	/* And square not pressed */
	       sqmark(x,y)!=1) {
	 sqpress(x,y)=YES;
	 Set_square(x,y,0);
      }
      else if (!mouse_status &&		/* Left button released */
	       !sqopen(x,y)  &&
	       sqpress(x,y)  &&
	       sqmark(x,y)!=1) {    	/* Open the square */
	 if (value(x,y) == MINE) {
	    Blow_up();
	    break;
	 }
	 else
	    Open_square(x,y);
      }
      else if (mouse_status==3 &&
	       sqopen(x,y)     &&
	       mrstant!=mouse_status) {	/* Open near squares */
	 mrstant=mouse_status;
	 if (Open_near_squares(x,y) == YES) {
	    Blow_up();
	    break;
	 }
      }
   }
   mouse_disable();
   return (getch());
}	/* Do_all */

/*----------------------------------------------------------------------*/

void Blow_up(void)
{
   int x, y, xl, yt, xr, yb;

   mouse_disable();
   for (x=0; x<ncx; x++) {
      for (y=0; y<ncy; y++) {
	 if (value(x,y) == MINE) {
	    settextjustify(CENTER_TEXT, CENTER_TEXT);
	    setcolor(LIGHTRED);
	    outtextxy(XST+XPX*x+XPX/2-1, YST+YPX*y+YPX/2, "л");
	    setcolor(BLACK);
	    outtextxy(XST+XPX*x+XPX/2, YST+YPX*y+YPX/2+1, "*");
	 }
	 else if (sqmark(x,y)==1) {
	    setcolor(YELLOW);
	    xl=XST+XPX*x;
	    xr=xl+XPX-1;
	    yt=YST+YPX*y;
	    yb=yt+YPX-1;
	    line(xl,yt,xr,yb);
	    line(xl,yb,xr,yt);
	 }
      }
   }
}	/* Blow_up */

/*----------------------------------------------------------------------*/

void Open_square(int x, int y)
{
   char num[2]="0";
   int a, b, c;

   sqopen(x,y)=YES;
   if ((num[0]=value(x,y)) != 0) {
      num[0]+='0';
      switch(num[0]) {
	 case '1' : c=LIGHTBLUE; break;
	 case '2' : c=LIGHTGREEN; break;
	 case '3' : c=YELLOW; break;
	 case '4' : c=LIGHTRED; break;
	 default  : c=LIGHTMAGENTA;
      }
      mouse_disable();
      setcolor(c);
      settextjustify(CENTER_TEXT, CENTER_TEXT);
      outtextxy(XST+XPX*x+XPX/2, YST+YPX*y+YPX/2+1, num);
      mouse_enable();
   }
   else {		/* Open near squares if the current number is 0 */
      a=x-1;
      b=y-1;
      if (a>=0 && b>=0 && a<ncx && b<ncy && !sqopen(a,b) && sqmark(a,b)!=1) {
	 Set_square(a,b,0);
	 Open_square(a,b);
      }
      a++;
      if (a>=0 && b>=0 && a<ncx && b<ncy && !sqopen(a,b) && sqmark(a,b)!=1) {
	 Set_square(a,b,0);
	 Open_square(a,b);
      }
      a++;
      if (a>=0 && b>=0 && a<ncx && b<ncy && !sqopen(a,b) && sqmark(a,b)!=1) {
	 Set_square(a,b,0);
	 Open_square(a,b);
      }
      b++;
      if (a>=0 && b>=0 && a<ncx && b<ncy && !sqopen(a,b) && sqmark(a,b)!=1) {
	 Set_square(a,b,0);
	 Open_square(a,b);
      }
      a-=2;
      if (a>=0 && b>=0 && a<ncx && b<ncy && !sqopen(a,b) && sqmark(a,b)!=1) {
	 Set_square(a,b,0);
	 Open_square(a,b);
      }
      b++;
      if (a>=0 && b>=0 && a<ncx && b<ncy && !sqopen(a,b) && sqmark(a,b)!=1) {
	 Set_square(a,b,0);
	 Open_square(a,b);
      }
      a++;
      if (a>=0 && b>=0 && a<ncx && b<ncy && !sqopen(a,b) && sqmark(a,b)!=1) {
	 Set_square(a,b,0);
	 Open_square(a,b);
      }
      a++;
      if (a>=0 && b>=0 && a<ncx && b<ncy && !sqopen(a,b) && sqmark(a,b)!=1) {
	 Set_square(a,b,0);
	 Open_square(a,b);
      }
   }
}	/* Open_square */

/*----------------------------------------------------------------------*/

/*
   Open the sorrounded squares. Returns != 0 if I activated a mine
*/
int Open_near_squares(int x, int y)
{
   int a, b, suma=0;

   a=x-1;
   b=y-1;
   if (a>=0 && b>=0 && a<ncx && b<ncy && sqmark(a,b)==1)
      suma++;
   a++;
   if (a>=0 && b>=0 && a<ncx && b<ncy && sqmark(a,b)==1)
      suma++;
   a++;
   if (a>=0 && b>=0 && a<ncx && b<ncy && sqmark(a,b)==1)
      suma++;
   b++;
   if (a>=0 && b>=0 && a<ncx && b<ncy && sqmark(a,b)==1)
      suma++;
   a-=2;
   if (a>=0 && b>=0 && a<ncx && b<ncy && sqmark(a,b)==1)
      suma++;
   b++;
   if (a>=0 && b>=0 && a<ncx && b<ncy && sqmark(a,b)==1)
      suma++;
   a++;
   if (a>=0 && b>=0 && a<ncx && b<ncy && sqmark(a,b)==1)
      suma++;
   a++;
   if (a>=0 && b>=0 && a<ncx && b<ncy && sqmark(a,b)==1)
      suma++;
   if (suma == value(x,y)) {
      suma=0;
      a=x-1;
      b=y-1;
      if (a>=0 && b>=0 && a<ncx && b<ncy && !sqopen(a,b) && sqmark(a,b)!=1) {
	 suma|=(value(a,b)==MINE);
	 Set_square(a,b,0);
	 Open_square(a,b);
      }
      a++;
      if (a>=0 && b>=0 && a<ncx && b<ncy && !sqopen(a,b) && sqmark(a,b)!=1) {
	 suma|=(value(a,b)==MINE);
	 Set_square(a,b,0);
	 Open_square(a,b);
      }
      a++;
      if (a>=0 && b>=0 && a<ncx && b<ncy && !sqopen(a,b) && sqmark(a,b)!=1) {
	 suma|=(value(a,b)==MINE);
	 Set_square(a,b,0);
	 Open_square(a,b);
      }
      b++;
      if (a>=0 && b>=0 && a<ncx && b<ncy && !sqopen(a,b) && sqmark(a,b)!=1) {
	 suma|=(value(a,b)==MINE);
	 Set_square(a,b,0);
	 Open_square(a,b);
      }
      a-=2;
      if (a>=0 && b>=0 && a<ncx && b<ncy && !sqopen(a,b) && sqmark(a,b)!=1) {
	 suma|=(value(a,b)==MINE);
	 Set_square(a,b,0);
	 Open_square(a,b);
      }
      b++;
      if (a>=0 && b>=0 && a<ncx && b<ncy && !sqopen(a,b) && sqmark(a,b)!=1) {
	 suma|=(value(a,b)==MINE);
	 Set_square(a,b,0);
	 Open_square(a,b);
      }
      a++;
      if (a>=0 && b>=0 && a<ncx && b<ncy && !sqopen(a,b) && sqmark(a,b)!=1) {
	 suma|=(value(a,b)==MINE);
	 Set_square(a,b,0);
	 Open_square(a,b);
      }
      a++;
      if (a>=0 && b>=0 && a<ncx && b<ncy && !sqopen(a,b) && sqmark(a,b)!=1) {
	 suma|=(value(a,b)==MINE);
	 Set_square(a,b,0);
	 Open_square(a,b);
      }
      return (suma);
   }
   else
      return 0;
}	/* Open_near_squares */
