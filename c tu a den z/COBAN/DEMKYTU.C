#include <stdio.h>
#include <ctype.h>

void main()
{
  FILE *fp;
  char sf[50], c;
  long count = 0;

  printf("\nNhap vao ten tap tin : ");
  scanf("%s", sf);
  if ((fp = fopen(sf, "r")) == NULL)
    fprintf(stderr, "\nKhong the mo tap tin %s", sf);
  else
  {
     while ((c = fgetc(fp)) != EOF)
       if (isalpha(c))
         count++;
     printf("\nSo ky tu trong %s la %ld", sf, count);
  }

  getch();
}