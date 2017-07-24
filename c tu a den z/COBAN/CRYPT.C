/* Ma hoa thong diep */
#include <stdio.h>
#include <ctype.h>

char *crypt(char *tdiep, int column)
{
  char tam[255], *result;
  int i = 0, k = 0, n, j=0;

  while(tdiep[i] != 0)
  {
    if (isalnum(tdiep[i]))
      tam[k++] = tdiep[i];
    i++;
  }
  tam[k] = 0;
  result = (char *)malloc(k+1);
  for (i=0; i<column; i++)
  {
    n = 0;
    while(n+i < k)
    {
      result[j++] = tolower(tam[n+i]);
      n += column;
    }
  }
  result[k] = 0;
  return result;
}

void main()
{
  char thongdiep[255], *mahoa;
  int col;

  printf("\nNhap thong diep can ma hoa : ");
  gets(thongdiep);
  printf("\nCho biet so cot : ");
  scanf("%d", &col);
  mahoa = crypt(thongdiep, col);
  printf("\nThong diep da duoc ma hoa thanh : %s", mahoa);
  getch();
}