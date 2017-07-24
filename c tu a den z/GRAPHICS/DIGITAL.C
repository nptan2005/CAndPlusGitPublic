/* Digital */
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <mem.h>
#include <string.h>

char tinhieu1[41], tinhieu2[41];

void screen()
{
  int i, n=0;
  char s[2] = "1";
  cleardevice();
  setcolor(BLUE);
  rectangle(0, 0, getmaxx(), getmaxy());
  for (i=0; i<41; i++)
  {
    setcolor(YELLOW);
    strset(s, tinhieu1[i]);
    outtextxy(64 + i * 14, 10, s);
    setcolor(CYAN);
    strset(s, tinhieu2[i]);
    outtextxy(64 + i * 14, 25, s);
    setcolor(BLUE);
    line(60 + i * 14, 40, 60 + i * 14, 40+19*14);
  }
  for (i=0; i<20; i++)
  {
    switch(n)
    {
      case 1 : outtextxy(42, 36+i*14, " 1"); break;
      case 2 : outtextxy(42, 36+i*14, " 0"); break;
      case 3 : outtextxy(42, 36+i*14, "-1");break;
    }
    n++;
    n %= 4;
    line(60, 40+i*14, 60+40*14, 40+i*14);
  }
  setcolor(WHITE);
  outtextxy(12, 36 + 2 * 14, "TH1");
  outtextxy(12, 36 + 6 * 14, "TH2");
  outtextxy(12, 36 + 10 * 14, "AND");
  outtextxy(12, 36 + 14 * 14, " OR");
  outtextxy(12, 36 + 18 * 14, "XOR");
  outtextxy(100, 400, "Nhan phim bat ky de bat dau, ESCAPE de ket thuc");
}

void run()
{
  int done = 0, OK = 1, i, first=1;
  do {
    screen();
    if (first)
    {
      getch();
      while (kbhit())
        getch();
      first = 0;
    }
    i = 0;
    OK = 1;
    do {
      setwritemode(XOR_PUT);
      setcolor(RED);
      line(60+i, 40, 60+i, 40+ 19*14);
      delay(50);
      line(60+i, 40, 60+i, 40+ 19*14);
      setwritemode(COPY_PUT);
      setcolor(YELLOW);
      if (tinhieu1[i/14] == '0')
        putpixel(60+i, 40+2*14, YELLOW);
      else
        putpixel(60+i, 40+1*14, YELLOW);
      if (i % 14 == 0 && i != 0)
        if (tinhieu1[i/14] != tinhieu1[(i-1)/14])
          line(60+i, 40+1*14, 60+i, 40+2*14);

      if (tinhieu2[i/14] == '0')
        putpixel(60+i, 40+6*14, YELLOW);
      else
        putpixel(60+i, 40+5*14, YELLOW);
      if (i % 14 == 0 && i != 0)
        if (tinhieu2[i/14] != tinhieu2[(i-1)/14])
          line(60+i, 40+5*14, 60+i, 40+6*14);

      if ((tinhieu1[i/14] & tinhieu2[i/14]) == '0')
        putpixel(60+i, 40+10*14, YELLOW);
      else
        putpixel(60+i, 40+9*14, YELLOW);
      if (i % 14 == 0 && i != 0)
        if ((tinhieu1[i/14] & tinhieu2[i/14])!= (tinhieu1[(i-1)/14] & tinhieu2[(i-1)/14]))
          line(60+i, 40+9*14, 60+i, 40+10*14);

      if ((tinhieu1[i/14] | tinhieu2[i/14]) == '0')
        putpixel(60+i, 40+14*14, YELLOW);
      else
        putpixel(60+i, 40+13*14, YELLOW);
      if (i % 14 == 0 && i != 0)
        if ((tinhieu1[i/14] | tinhieu2[i/14])!= (tinhieu1[(i-1)/14] | tinhieu2[(i-1)/14]))
          line(60+i, 40+13*14, 60+i, 40+14*14);

      if ((tinhieu1[i/14] ^ tinhieu2[i/14]) == 0)
        putpixel(60+i, 40+18*14, YELLOW);
      else
        putpixel(60+i, 40+17*14, YELLOW);
      if (i % 14 == 0 && i != 0)
        if ((tinhieu1[i/14] ^ tinhieu2[i/14])!= (tinhieu1[(i-1)/14] ^ tinhieu2[(i-1)/14]))
          line(60+i, 40+17*14, 60+i, 40+18*14);

      i++;
      if (i>40 * 14)
        OK = 0;
      if (kbhit())
      {
        done = 1;
        OK = 0;
      }
    } while (OK);
    setwritemode(COPY_PUT);
  } while (!done);
}

void main()
{
  int gr_drive = DETECT, gr_mode, n=0;
  char c;

  memset(tinhieu1, '0', 40);
  memset(tinhieu2, '0', 40);
  printf("\nNhap chuoi tin hieu 1 (toi da 40) : \n");
  do {
    do {
      c = getch();
    } while (c != '0' && c!='1' && c != 27 && c != 13);
    if (c == '1' || c == '0')
    {
      tinhieu1[n++] = c;
      putc(c, stdout);
    }
  } while (c != 13 && c != 27 && n<=40);
  n = 0;
  printf("\nNhap chuoi tin hieu 2 (toi da 40) : \n");
  do {
    do {
      c = getch();
    } while (c != '0' && c!='1' && c != 27 && c != 13);
    if (c == '1' || c == '0')
    {
      tinhieu2[n++] = c;
      putc(c, stdout);
    }
  } while (c != 13 && c != 27 && n<=40);
  printf("\n%s", tinhieu1);
  printf("\n%s", tinhieu2);
  getch();
  initgraph(&gr_drive, &gr_mode, "");
  run();
  closegraph();
}