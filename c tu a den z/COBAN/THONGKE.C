/* Bai tap 1_67 - Tim so dong, so tu, so ky tu nhap tu ban phim */
#include <stdio.h>

void main()
{
  int sokytu=0, dautu = 0, sotu=0, sodong=1;
  char c, filename[50];
  FILE *fp;

  printf("\nCho biet ten tap tin muon xem : ");
  gets(filename);
  if ((fp = fopen(filename, "r")) == NULL)
    printf("Khong tim thay tap tin %s", filename);
  else
  {
    do {
      putc(c = fgetc(fp), stdout);
      if (c != '\n' && c != EOF)
        sokytu++;
      if (isalnum(c) && dautu == 0)
      {
        sotu++;
        dautu=1;
      }
      if (!isalnum(c) && dautu == 1)
        dautu = 0;
      if (c == '\n')
        sodong++;
    } while (c != EOF);
    fclose(fp);
    printf("\n\nSo dong : %d", sodong);
    printf("\nSo tu : %d", sotu);
    printf("\nSo ky tu : %d", sokytu);
  }
  getch();
}