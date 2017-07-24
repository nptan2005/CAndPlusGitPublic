/* Doc tap tin CHR */
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <dos.h>
#include <alloc.h>
#include <ctype.h>
#include "mouse.inc"

int x, y;
unsigned char lbutton, rbutton;
int already = 0;

#define NUMMENUS 3
char menu[NUMMENUS][10] = {
  "Load File",
  "-",
  "Quit"
  };

typedef struct tagheader {
  char sign[4];        /* Phai bang "PK", 8, 8*/
  char version[0x54];  /* "BGI Stroked Font..." */
  unsigned char rev1;  /* = 0x1A */
  unsigned headersize; /* Thuong bang 0x80 */
  char fontname[4];    /* Ten font */
  char pad[33];        /* Cho du kich thuoc 0x80 */
} HEADER;

typedef struct tagfontinfo {
  char sign;          /* Luon bang 0x2B */
  unsigned numchar;   /* So luong ky tu trong font */
  unsigned char dump1;
  char startchar;     /* Ky tu bat dau */
  unsigned startoffset; /* Chi so bat dau chua du lieu + 80h cua header */
  char pad[9];        /* Cho du kich thuoc 0x10 */
} FONTINFO;

HEADER header;
FONTINFO fontinfo;
unsigned offset[256]; /* Bang chua offset */
unsigned char width[256]; /* Bang chua be rong chu */
unsigned char curchar;

char filename[50];
FILE *fp;
typedef struct tagstroke {
  unsigned char x, y;
} STROKE;

STROKE stroke [1000];
int numstroke;

void getmouse()
{
  do {
    get_mouse_button(&lbutton, &rbutton, &x, &y);
  } while (lbutton == 0 && rbutton == 0);
}

void clearmouse()
{
  while (lbutton || rbutton)
    get_mouse_button(&lbutton, &rbutton, &x, &y);
}

void paintarea()
{
  int i, j;

  setcolor(BLACK);
  setfillstyle(SOLID_FILL, BLACK);
  bar(1, 1, 479, 478);
  for (i=0; i<60; i++)
    for (j=0; j<60; j++)
      putpixel(i*8, j*8, GREEN);
}

void screen()
{
  int i;
  char s[50];
  cleardevice();
  setcolor(GREEN);
  rectangle(0, 0, getmaxx(), getmaxy());
  line(480, 0, 480, getmaxy());
  for (i=0; i<3; i++)
  { if (strcmp(menu[i], "-") == 0)
      line(500, 30 + i * 16, 600, 30 + i * 16);
    else
    {
      setcolor(YELLOW);
      strncpy(s, menu[i], 1);
      s[1] = 0;
      outtextxy(500, 30 + i * 16, s);
      setcolor(WHITE);
      strncpy(s, menu[i]+1, strlen(menu[i])-1);
      s[strlen(menu[i])-1] = 0;
      outtextxy(508, 30 + i * 16, s);
    }
  }
  outtextxy(500, 100, "Thay doi ky tu");
  outtextxy(500, 116, "UP   : truoc");
  outtextxy(500, 132, "DOWN : sau");
  paintarea();
}

void showchar()
{
  int i, x, y;
  int codex, codey;
  paintarea();
  fp = fopen(filename, "rb");
  fseek(fp, offset[curchar-fontinfo.startchar]+sizeof(HEADER)+
            fontinfo.startoffset, SEEK_SET);
  numstroke = 0;
  do {
    fread(&stroke[numstroke], sizeof(STROKE), 1, fp);
    codex = (stroke[numstroke].x & 0x80) >> 7;
    codey = (stroke[numstroke].y & 0x80) >> 7;
    numstroke++;
  } while (codex != 0 || codey != 0);
  setcolor(WHITE);
  for (i=0; i<numstroke; i++)
  {
    x = (int)(stroke[i].x & 0x7F);
    if (x > 0x3F)
      x = x - 0x80;
    y = (int)(stroke[i].y & 0x7F);
    if (y > 0x3F)
      y = y- 0x80;
    codex = (stroke[i].x & 0x80) >> 7;
    codey = (stroke[i].y & 0x80) >> 7;
    if (codex == 1 && codey == 0)
      moveto(getmaxy()/2 + (x-10)*8, getmaxy()/2 - (y-10)*8);
    else if (codex == 1 && codey == 1)
      lineto(getmaxy()/2 + (x-10)*8, getmaxy()/2 - (y-10)*8);
  }
  fclose(fp);
}

void LoadFile()
{
  int i = 0;
  char c;
  char s[5] = "C";

  hide_mouse();
  setcolor(BLACK);
  setfillstyle(SOLID_FILL, BLACK);
  bar(getmaxx()/2 - 200, getmaxy()/2-20, getmaxx()/2+100, getmaxy()/2+20);
  setcolor(YELLOW);
  rectangle(getmaxx()/2 - 200, getmaxy()/2-20, getmaxx()/2+100, getmaxy()/2+20);
  rectangle(getmaxx()/2 - 198, getmaxy()/2-18, getmaxx()/2+98, getmaxy()/2+18);
  setwritemode(XOR_PUT);
  do {
    c = toupper(getch());
    if (c == 8 && i>0)
    {
      setcolor(BLACK);
      i--;
      s[0] = filename[i];
      outtextxy(i*textwidth(s)+getmaxx()/2-190, getmaxy()/2-2, s);
      setcolor(YELLOW);
    }
    else if (c!= 13 && c !=27 && i<36)
    {
      s[0] = c;
      outtextxy(i*textwidth(s)+getmaxx()/2-190, getmaxy()/2-2, s);
      filename[i] = c;
      i++;
    }
  } while (c != 13 && c != 27);
  if (c == 13)
    filename[i] = 0;
  if ((fp = fopen(filename, "rb")) == NULL)
  {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    bar(getmaxx()/2 - 197, getmaxy()/2-17, getmaxx()/2+97, getmaxy()/2+17);
    setcolor(YELLOW);
    outtextxy(getmaxx()/2-190, getmaxy()/2-2, "Khong the mo tap tin");
    getch();
  }
  else
  {
    fread(&header, sizeof(HEADER), 1, fp);
    if (header.sign[0] != 'P' && header.sign[1] != 'K' &&
        header.sign[2] != 8 && header.sign[3] != 8)
    {
      setcolor(BLACK);
      setfillstyle(SOLID_FILL, BLACK);
      bar(getmaxx()/2 - 197, getmaxy()/2-17, getmaxx()/2+97, getmaxy()/2+17);
      setcolor(YELLOW);
      outtextxy(getmaxx()/2-190, getmaxy()/2-2, "Khong phai la tap tin CHR");
      getch();
    }
    else
    {
      memcpy(&s, &header.fontname, 4);
      s[4] = 0;
      outtextxy(500, getmaxy()-50,s);
      fread(&fontinfo, sizeof(FONTINFO), 1, fp);
      fread(&offset, sizeof(unsigned), fontinfo.numchar, fp);
      fread(&width, sizeof(unsigned char), fontinfo.numchar, fp);
      curchar = fontinfo.startchar;
      already = 1;
      showchar();
      fclose(fp);
      return;
    }
    fclose(fp);
  }
  paintarea();
  show_mouse();
}

void PrevChar()
{
  if (already == 0)
    return;
  if (curchar > fontinfo.startchar)
  {
    curchar--;
    showchar();
  }
}

void NextChar()
{
  if (already == 0)
    return;
  if (curchar < fontinfo.startchar+fontinfo.numchar)
  {
    curchar++;
    showchar();
  }
}

void run()
{
  char c;
  screen();
  do {
    if (kbhit())
    {
      c = getch();
      if (c == 0)
        c = getch();
      switch(c)
      {
        case 'L' :
        case 'l' : LoadFile();
                   break;
        case 'Q' :
        case 'q' : c = 27;
                   break;
        case 72  : PrevChar(); break;
        case 80  : NextChar(); break;
      }
    }
  } while (c != 27);
}

void main()
{
  int gr_drive = DETECT, gr_mode;

  initgraph(&gr_drive, &gr_mode, "");
  reset_mouse();
  show_mouse();
  run();
  closegraph();
}