/* Bai tap 1_90 - Minh hoa phuong phap sap xep doi cho truc tiep */
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <dos.h>

#define MAX 10   // so luong phan tu toi da (khong duoc qua 10)
#define DONG 10  // dong bat dau in mang
#define DELAY 300

int  mang[MAX];  // Bien toan cuc
int cot = (80 - 5 * MAX) / 2;

void hoandoi(int i, int j)
{
  int xi = cot + 2 + i * 5;
  int xj = cot + 2 + j * 5;
  int xdest = xj;
  int yi = DONG + 1;
  int yj = DONG + 1;
  int k, l;
  textcolor(YELLOW);
  for (k = 0; k<2; k++)
  {
	gotoxy(xi,yi--);
	cprintf("  ");
	gotoxy(xj,yj++);
	cprintf("  ");
	gotoxy(xi,yi);
	cprintf("%2d",mang[i]);
	gotoxy(xj,yj);
	cprintf("%2d",mang[j]);
	delay(DELAY);
  }
  while (xi<xdest)
  {
	gotoxy(xi++,yi);
	cprintf("  ");
	gotoxy(xj--,yj);
	cprintf("  ");
	gotoxy(xi,yi);
	cprintf("%2d",mang[i]);
	gotoxy(xj,yj);
	cprintf("%2d",mang[j]);
	delay(DELAY);
  }
  for (k = 0; k<2; k++)
  {
	gotoxy(xi,yi++);
	cprintf("  ");
	gotoxy(xj,yj--);
	cprintf("  ");
	gotoxy(xi,yi);
	cprintf("%2d",mang[i]);
	gotoxy(xj,yj);
	cprintf("%2d",mang[j]);
	delay(DELAY);
  }
  xdest   = mang[i];
  mang[i] = mang[j];
  mang[j] = xdest;
}

void in_bien_i(int i)
{
  gotoxy(cot+(i-1)*5+1,DONG-3);
  textcolor(BLACK);
  cprintf("%c",25);
  gotoxy(cot+(i)*5+1,DONG-3);
  textcolor(WHITE + BLINK);
  cprintf("%c",25);
  delay(DELAY);
}

void in_bien_j(int j)
{
  gotoxy(cot+(j-1)*5+1,DONG+5);
  textcolor(BLACK);
  cprintf("%c",24);
  gotoxy(cot+(j)*5+1,DONG+5);
  textcolor(WHITE + BLINK);
  cprintf("%c",24);
  delay(DELAY);
}

void main()
{
// Phan khai bao bien
  char tieude[]="CHUONG TRINH DEMO MOT PHUONG PHAP SAP XEP (SORT)";
  char khungtrai[3] = {'ษ','บ','ศ'};
  char khungtrong[3] = {'ห','บ','ส'};
  char khungphai[3] = {'ป','บ','ผ'};
  char c;
  int i, j;

// Xoa man hinh
  textmode(C80);
  textattr(14);
  clrscr();

// In dong tieu de
  gotoxy((80-strlen(tieude))/2,2);
  cprintf("%s",tieude);

// Khoi tao mang mot cach ngau nhien
  randomize();
  for (i=0; i<MAX; i++)
	mang[i] = random(100);

// In mang ra man hinh
  textcolor(WHITE);
  for (i=0;i<3;i++)
  {
	gotoxy(cot,DONG+i);
	cprintf("%c", khungtrai[i]);
  }
  for (j=0; j<MAX; j++)
  {
	 textcolor(WHITE);
	 gotoxy(cot+j*5+1,DONG);
	 cprintf("อ  ออ");
	 textcolor(YELLOW);
	 gotoxy(cot+j*5+2,DONG+1);
	 cprintf("%2d",mang[j]);
	 textcolor(WHITE);
	 gotoxy(cot+j*5+1,DONG+2);
	 cprintf("อ  ออ");
	 for (i=0;i<3;i++)
	 {
	   gotoxy(cot+(j+1)*5,DONG+i);
	   cprintf("%c", khungtrong[i]);
	 }
  }
  for (i=0;i<3;i++)
  {
	gotoxy(cot+MAX*5,DONG+i);
	cprintf("%c", khungphai[i]);
  }

// In cau thong bao va cho nguoi su dung nhan phim de thuc hien
  textcolor(11);
  gotoxy (1,24);
  cprintf("Nhan phim A : Sap xep tang dan - D : Sap xep giam dan");
  gotoxy (1,DONG-4);
  cprintf("Bien i");
  gotoxy (1,DONG+6);
  cprintf("Bien j");
  do
  {
	c = toupper(getch());
  } while ((c != 'A') && (c != 'D'));

// Bat dau thuc hien sap xep
  switch (c)
  {
	case 'A' :
			   for (i=0; i<MAX-1; i++)
			   {
				 in_bien_i(i);
				 for (j=i+1; j<MAX; j++)
				 {
				   in_bien_j(j);
				   if (mang[i] > mang[j])
					 hoandoi(i,j);
				 }
				 gotoxy(cot+(j-1)*5+1,DONG+5);
				 textcolor(BLACK);
				 cprintf("%c",24);
			   }
			   break;
	case 'D' :
			   for (i=0; i<MAX-1; i++)
			   {
				 in_bien_i(i);
				 for (j=i+1; j<MAX; j++)
				 {
				   in_bien_j(j);
				   if (mang[i] < mang[j])
					 hoandoi(i,j);
				 }
				 gotoxy(cot+(j-1)*5+1,DONG+5);
				 textcolor(BLACK);
				 cprintf("%c",24);
			   }
			   break;
  }
  gotoxy(cot+(i-1)*5+1,DONG-3);
  textcolor(BLACK);
  cprintf("%c",25);

// Thong bao va cho nguoi dung nhan phim de ket thuc
  gotoxy(1,24);
  clreol();
  textcolor(13+BLINK);
  cprintf("Nhan phim bat ky de ket thuc");
  getch();
}
