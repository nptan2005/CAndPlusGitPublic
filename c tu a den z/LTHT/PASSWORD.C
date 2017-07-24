/* Bai tap 4_2 - Xoa Password cua CMOS */
#include <dos.h>

void xoaCMOS()
{
  outp(0x70, 0x10);
  outp(0x70, 0);
}

void main()
{
  char c;
  printf("\nNhan phim bat ky de xoa CMOS hoac phim ESCAPE de ngung"
  "\nLuu y : CMOS luu giu cac thong tin nhu : ngay thang, thong tin ve o dia,..."
  "\nnen sau khi xoa xong, ta phai thiet lap lai chung thi may moi hoat dong dung."
  "\nNeu thu nghiem thi truoc khi thuc hien, ban hay ghi lai cac thong tin do.");
  c = getch();
  if (c != 27)
  {
    xoaCMOS();
    printf("\CMOS da duoc xoa");
  }
}