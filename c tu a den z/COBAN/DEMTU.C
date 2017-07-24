#include <stdio.h>
#include <ctype.h>

void main()
{
  FILE *fp;
  char sf[50], chuoi[250];
  int len, i;
  long count = 0;

  printf("\nNhap vao ten tap tin : ");
  scanf("%s", sf);
  if ((fp = fopen(sf, "r")) == NULL)
    fprintf(stderr, "\nKhong the mo tap tin %s", sf);
  else
  {
     while (fgets(chuoi, 250, fp) != NULL)
     {
       len = strlen(chuoi) - 1;
       i=0;
       do {
        while (chuoi[i] == ' ' && i <= len-1)
           i++;
         if (i<=len-1)
         {
           while (isalnum(chuoi[i]))
             i++;
           count++;
         }
       } while (i <= len-1);
     }
     printf("\nSo ky tu trong %s la %ld", sf, count);
  }

  getch();
}