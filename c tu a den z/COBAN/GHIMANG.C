/* Bai tap 1_86 - Doc va ghi len file mot mang 2 chieu 10x10 */
#include <stdio.h>

#define MAX 10

char filename[] = "MANG1010.DAT";

void main()
{
  int mang[MAX][MAX], i, j;
  FILE *fp;

  if ((fp = fopen(filename, "w+")) == NULL)
    printf("\nKhong the tao tap tin %s", filename);
  else
  {
    printf("\nNhap cac phan tu cua mang : ");
    for (i=0; i<MAX; i++)
      for (j=0; j<MAX; j++)
      {
        printf("\nMang[%d][%d] = ", i, j);
        scanf("%d", &mang[i][j]);
      }
    fwrite(&mang, sizeof(int), MAX * MAX, fp);
    fclose(fp);
    printf("\nViec ghi hoan tat.");
  }
  getch();
}