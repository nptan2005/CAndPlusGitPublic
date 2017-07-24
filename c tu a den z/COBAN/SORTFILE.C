/* Bai tap 1_66 - Sort tap tin */
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

void main()
{
  int i, j, mang[MAX], m;
  FILE *fp;

  randomize();
  if ((fp = fopen("SFILE.DAT", "w+")) == NULL)
    printf("\nKhong the tao tap tin SFILE.DAT");
  else
  {
    printf("\n");
    for (i=0; i<MAX; i++)
    { m = random(100);
      fprintf(fp, "%d ", m);
      printf("%d ", m);
    }
    fclose(fp);

    fp = fopen("SFILE.DAT", "r");
    for (i=0; i<MAX; i++)
      fscanf(fp, "%d", &mang[i]);
    fclose(fp);

    for (i=0; i<MAX-1; i++)
      for (j=i+1; j<MAX; j++)
        if (mang[j] < mang[i])
        {
          m = mang[i];
          mang[i] = mang[j];
          mang[j] = m;
        }
    printf("\n");
    fp = fopen("SFILE2.DAT", "w+");
    for (i=0; i<MAX; i++)
    {
      fprintf(fp, "%d ", mang[i]);
      printf("%d ", mang[i]);
    }
    fclose(fp);
  }
  getch();
}