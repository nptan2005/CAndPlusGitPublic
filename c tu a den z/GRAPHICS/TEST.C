#include <dos.h>
#include <graphics.h>
#include "mouse.inc"

void main()
{
   int gd = DETECT, gm;
   char CMXs[10];

   initgraph(&gd, &gm, "");
   reset_mouse();
   install_event_handler();
   show_mouse();
   while(!kbhit())
   {
     if (CURSOR_MOVED)
     {
       hide_mouse();
       itoa(CMX, CMXs, 10);
       setcolor(0);
       setfillstyle(SOLID_FILL, BLACK);
       bar(100, 100, 300, 140);
       setcolor(4);
       outtextxy(100, 100, CMXs);
     }
   }
   getch();
   closegraph();
}