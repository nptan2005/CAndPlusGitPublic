/* Bai tap 1_70 - Ma hoa 1 file bang phep XOR */
#include <stdio.h>

void main()
{
  char c, filein[50], fileout[50], key;
  FILE *fpin, *fpout;

  printf("\nCho biet ten tap tin nguon : ");
  gets(filein);
  printf("\nCho biet ten tap tin dich : ");
  gets(fileout);
  printf("\nCho biet khoa : ");
  scanf("%c", &key);
  if ((fpin = fopen(filein, "r")) == NULL)
    printf("Khong tim thay tap tin %s", filein);
  else
    if ((fpout = fopen(fileout, "w+")) == NULL)
    {
      printf("Khong the tao tap tin %s", fileout);
      fclose(fpin);
    }
    else
    {
      do {
        c = fgetc(fpin);
        if (c != EOF)
          fputc(c ^ key, fpout);
      } while (c != EOF);
      fclose(fpin);
      fclose(fpout);
      printf("\nCong viec hoan tat");
    }

  getch();
}