#include <stdio.h>

void main(int argc, char *argv[])
{
  FILE *fp;
  char c;

  if (argc <= 1)
    printf("\nCach su dung : \nHienfile <ten tap tin>");
  else
    if ((fp = fopen(argv[1], "r")) == NULL)
       printf("\nKhong the mo tap tin %s", argv[1]);
    else
    {
       while ((c = fgetc(fp)) != EOF)
         putc(c, stdout);
    }
  getch();
}