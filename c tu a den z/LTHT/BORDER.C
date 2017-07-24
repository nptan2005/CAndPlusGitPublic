/* Change Border */
#include <stdio.h>

#define MXCOLOR 15

void border_change(int color)
{
  asm {
    mov ah, 11
    mov bx, color
    int 10h
  }
}

void main( int argc, char *argv[] )
{
   int brd_color=0, delay, i, j;

   if( argc <= 1 ){
      printf( "\nNhap vao mot so tu 0 den 15 de chi mau duong vien.");
      printf( "\n     0 - Black      5 - Purple      10 - Bright Green     15 - Light Cyan" );
      printf( "\n     1 - Blue       6 - Yellow      11 - Light Cyan" );
      printf( "\n     2 - Green      7 - White       12 - Orange" );
      printf( "\n     3 - Cyan       8 - Dark Green  13 - Purple");
      printf( "\n     4 - Red        9 - Light Blue  14 - Green");
      printf( "\nChon : ");
      scanf( "%d", &brd_color );
   }
   else {
      sscanf( argv[1], "%d", &brd_color );
      border_change( brd_color );
   }

   while( brd_color < 0 || brd_color > MXCOLOR )
   {
      printf("\n\aGia tri khong hop le! Chi nhap nhung gia tri giua 0 and 15: ");
      scanf("%d", &brd_color);
   }
   border_change( brd_color );
}
