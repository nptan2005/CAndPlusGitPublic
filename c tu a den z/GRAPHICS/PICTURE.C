#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<math.h>
#define CLIP_ON 1
#define pi 3.14
int n,t,ll;
float hs,hsd,go;
//--------------------------------------------------------------------------
void linefractal(int x1,int y1,int x2,int y2,int l,int k)
{
  int y0,x0,x,cc,i,ttt;
  float hsg,yz,r,tttt;
  if (k > 0)
    {
       x0 = (x1+x2) /2 - (random(1000)*0.001)*hsd*(y2-y1);
       y0 = (y1+y2) /2 - (random(1000)*0.001)*hsd*(x2-x1);
       linefractal(x1,y1,x0,y0,l,k-1);
       linefractal(x0,y0,x2,y2,l,k-1);
    }
  else
    {
       if ((x2-x1) != 0)
	 {
	    hsg = (y2-y1)/(x2-x1);
	    yz = y1;
	    for (x = x1; x <= x2; x++)
	       {
		  yz = yz + hsg;
		  line(x,(int)yz,x,l);
		  for (i = 1; i<=(ttt=(int)((l-yz)/8));i++)
		     {
			r = random(1000)*0.001;
			if (r >(tttt= (0.1 + (random(1000)*0.001)*0.5)))
			   cc = GREEN;
			else
			   if (r > (tttt=((random(1000)*0.001) * 0.6)))
			       cc = LIGHTBLUE;
			   else
			      cc = WHITE;
			      putpixel(x,(int)((1-r)*yz+r*l),cc);
		     }
	       }
	 }
    }
}
//--------------------------------------------------------------------------
int dau()
{
   if (random(2) == 0)
      return -1;
   else
      return 1;
}
//--------------------------------------------------------------------------

void cay(int x,int y,float h,float g,float gw,int k)
{
   int x1,y1,i,j,d,leaf,c;
   float dg,tt;
   if (k > 0)
      for (j = 1; j <= random(t) + t ; j++)
	 {
	    x1 = (int)(x + h * cos(g));
	    y1 = (int)(y + h * sin(g));
	    setcolor(DARKGRAY);
	    for (i = 0; i <= (int)((h/35)*(h/35)); i++)
	       {
		  line(x + i, y, x1 + i, y1);
		  for (d = 1; d <= (h/5); d++)
		     {
			tt = random(1000)*0.001;
			putpixel((int)((1-tt)*x+tt*x1)+i,(int)((1-tt)*y+tt*y1),LIGHTGRAY);
		     }
	       }
	    dg = gw/(2*n+1);
	    for (i = -n; i <= n; i++)
	       if ((random(1000)*0.001) > 0.5)
		  cay(x1,y1,h*(0.5+(random(1000)*0.001)/3),g+i*dg,gw*hs,k-1);
	       x = x1;
	       y = y1;
	       g = g - pi/18;
	 }
   else
     {
	setfillstyle(1,GREEN);
	setcolor(GREEN);
	for (leaf = 1; leaf <= 2; leaf++)
	   fillellipse(x+random(8)*dau(),y+random(5)*dau(),random(5)+2,random(2)+1);
	for (leaf = 1; leaf <= 70; leaf++)
	   {
	      switch (random(50))
		{
		   case 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20:
		     {
			  putpixel(x+random(15)*dau(),y+random(5)*dau(),BLUE);
			  break;
		     }
		   case 21,22,23,24,25:
		     {
			  putpixel(x+random(15)*dau(),y+random(5)*dau(),LIGHTBLUE);
			  break;
		     }
		   case 26,27,28,29,30,31,32,33,34,35,36,37,38,39,
			40,41,42,43,44,45,46,47,48,49:
		     {
			  putpixel(x+random(15)*dau(),y+random(5)*dau(),LIGHTGREEN);
			  break;
		     }
		}
	   }
     }
}

//--------------------------------------------------------------------------
void cloud(int x,int y,float Rx,float Ry,int k)
{
   int i;
   if (k > 0)
     for (i = 1; i <= 5; i++)
	cloud(x+random(Rx),y+random(Ry),Rx*0.8,Ry*0.6,k-1);
   else
     for (i = 1; i <= (sqrt(Rx*Ry)/3.5); i++)
	putpixel(x+random(Rx),y+random(Ry),WHITE);
}
//--------------------------------------------------------------------------
void phong()
{
   int i,j,x,y;
   ll = getmaxx() / 2;
   setfillstyle(1,LIGHTCYAN);
   bar(0,0,getmaxx(),ll);
   setfillstyle(1,LIGHTRED);
   pieslice(300,ll,0,180,100);
   setfillstyle(1,LIGHTBLUE);
   bar(0,ll,getmaxx(),getmaxy());
   for (i = 1; i <= 20000; i++)
      switch(random(8))
	 {
	    case 0,1,2,3,4:
	       {
		  putpixel(random(getmaxx()),ll+random(getmaxy()-ll),GREEN);
		  break;
	       }
	    case 5,6:
	       {
		  putpixel(random(getmaxx()),ll+random(getmaxy()-ll),YELLOW);
		  break;
	       }
	    case 7:
	       {
		  putpixel(random(getmaxx()),ll+random(getmaxy()-ll),LIGHTRED);
		  break;
	       }

	 }
   hsd = 0.4;
   for (i = 1; i <= 3+random(3); i++)
      {
	 x = random(getmaxx()-100);
	 setcolor(BLUE);
	 linefractal(x,ll,x+random(200)+50,ll,ll,6);
      }
   for (i = 1; i <= 5; i++)
      cloud(random(getmaxx()),random(80)+10,random(60)+60,random(40)+20,5);
   for (i = 1; i <= 2; i++)
      cay(i*((getmaxx()-100)/5)-random(100),-random(80),getmaxy()/(10+random(4))
		,pi/((random(1000)*0.001)*0.5+3),go,4);
   for (j = 1; j <= 200; j++)
     {
	x = random(getmaxx());
	y = ll+random(getmaxy()-ll);
	setcolor(LIGHTGRAY);
	for (i = 1; i <= 2; i++)
	   {
	      line(x,y+1,x-2,y);
	      line(x,y+1,x+2,y);
	   }
     }
   for (i = 1; i <= 3+random(3); i++)
      {
	 x = random(getmaxx() -100);
	 setcolor(BLUE);
	 y = ll + random(getmaxy()-ll);
	 linefractal(x,y,x+random(200)+50,y,y,6);
      }

}
//--------------------------------------------------------------------------
void main()
{
   int gd,gm,i,c;
   randomize();
   gd = DETECT;
   initgraph(&gd,&gm,"c:\\tc\\bgi");
   setviewport(0,0,getmaxx(),getmaxy(),CLIP_ON);
   do
     {
	 n = 1;
	 hs = 1.2;
	 go = pi/2.8;
	 t = 2;
	 phong();
	 c = getch();
      }while (c!=27);
   closegraph();
}