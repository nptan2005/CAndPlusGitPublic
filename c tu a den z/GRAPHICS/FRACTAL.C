#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<math.h>
#define pi 3.14
#define CLIP_ON 1
int n,c,t,mau;
float hs,go;
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
	    x1 = x + h * cos(g);
	    y1 = y + h * sin(g);
	    setcolor(DARKGRAY);
	    for (i = 0; i <= (h/35)*(h/35); i++)
	       {
		  line(x + i, y, x1 + i, y1);
		  for (d = 1; d <= (h/5); d++)
		     {
			tt = random(1);
			putpixel((1-tt)*x+tt*x1+i,(1-tt)*y+tt*y1,LIGHTGRAY);
		     }
	       }
	    dg = gw/(2*n+1);
	    for (i = -n; i <= n; i++)
	      if (random(1000)*0.001 > 0.5)
	       cay(x1,y1,h*(0.5+(random(1000)*0.001)/3),g+i*dg,gw*hs,k-1);
	    x = x1;
	    y = y1;
	    g = g + M_PI/18;
	 }
   else
     {
	setfillstyle(1,random(15));
	setcolor(random(15));
	for (leaf = 1; leaf <= 2; leaf++)
	   fillellipse(x+random(8)*dau(),y+random(5)*dau(),random(5)+2,random(2)+1);
	for (leaf = 1; leaf <= 70; leaf++)
	   {
	      switch (leaf)
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
		   case 26,27,28,29,30,31,32,33,34,35,36,37,38,39
			     ,40,41,42,43,44,45,46,47,48,49:

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
   int l,i;
   l = (getmaxy() / 7) * 5;
   setfillstyle(1,(mau=random(15)));
   bar(0,0,getmaxx(),l);
   setfillstyle(1,LIGHTGRAY);
   bar(0,l,getmaxx(),getmaxy());
   for (i = 1; i < 20000; i++)
      switch (random(8))
	 {
	    case 0,1,2,3,4:
	      {
		putpixel(random(getmaxx()),l+random(getmaxy()-l),GREEN);
		break;
	      }
	    case 5,6:
	      {
		putpixel(random(getmaxx()),l+random(getmaxy()-l),YELLOW);
		break;
	      }
	    case 7:
	      {
		putpixel(random(getmaxx()),l+random(getmaxy()-l),LIGHTRED);
		break;
	      }
	 }
   if (mau!=RED)
    {
      if (mau!=BLACK)
     {
       setfillstyle(1,RED);
       setcolor(RED);
     }
    }
   else
     {
       setfillstyle(1,YELLOW);
       setcolor(YELLOW);
     }
   fillellipse(random(getmaxx() / 2)+300,100,30,30);
   for (i = 1; i <= 5; i++)
      cloud(random(getmaxx()),random(150)+10,random(60)+60,random(40)+20,5);
}
//--------------------------------------------------------------------------
void main()
{
   int i,graphdriver,graphmode;
   char ch;
   randomize();
   graphdriver = DETECT; //graphmode;
   initgraph(&graphdriver, &graphmode,"C:\\TC\\BGI");
   setviewport(0,0,getmaxx(),getmaxy(),CLIP_ON);
   do
     {
	n = 1;
	hs = 1.2;
	go = M_PI /2.8;
	t = 2;
	phong();
	cay(((getmaxx()-100) /5)+random(60),(getmaxy()/ 7)*6+random(30)*dau(),getmaxy() / 6,-M_PI/2,go,5);
	ch= getch();
      }while (ch!=27);
   closegraph();
}