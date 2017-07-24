#include <stdio.h>
#include <string.h>

void main(int argc, char *argv[])
{
  FILE *fp;
  char s[255];

  if (argc <= 1)
    printf("\nCach su dung : \nHienfile <ten tap tin>");
  else
    if ((fp = fopen(argv[1], "r")) == NULL)
       printf("\nKhong the mo tap tin %s", argv[1]);
    else
      while (fgets(s, 255, fp))
      {
        s[strlen(s) - 1] = 0;
        if (strlen(s))
          puts(s);
      }
  getch();
}