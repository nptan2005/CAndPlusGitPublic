/* Bai tap 1_86 - Doc tu file mot mang 2 chieu 10x10 */
#include <stdio.h>

#define MAX 10

char filename[] = "MANG1010.DAT";

void main()
{
  int mang[MAX][MAX], i, j;
  FILE *fp;

  if ((fp = fopen(filename, "r")) == NULL)
    printf("\nKhong the mo tap tin %s", filename);
  else
  {
    fread(&mang, sizeof(int), MAX * MAX, fp);
    fclose(fp);
    printf("\nViec doc hoan tat.");
    for (i=0; i<MAX; i++)
    {
      printf("\n");
      for (j=0; j<MAX; j++)
        printf("%d ", mang[i][j]);
    }
  }
  getch();
}