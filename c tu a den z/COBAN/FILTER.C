/* Bai tap 1_68 - Tap hop thong tin */
#include <stdio.h>

void main()
{
  char s[100], s1[100], s2[100], filename1[50], filename2[50];
  FILE *fp1, *fp2;

  printf("\nCho viet ten tap tin thu nhat : ");
  gets(filename1);
  if ((fp1 = fopen(filename1, "w+")) == NULL)
    printf("\nKhong the tao tap tin %s", filename1);
  else
  {
    printf("\nCho viet ten tap tin thu nhat : ");
    gets(filename2);
    if ((fp2 = fopen(filename2, "w+")) == NULL)
      printf("\nKhong the tao tap tin %s", filename2);
    else
    {
      do {
        printf("\nHo ten (ENTER de ket thuc) : ");
        gets(s);
        if (strlen(s) > 0)
        {
          strcat(s, "\n");
          fputs(s, fp1);
          printf("\nTuoi : ");
          gets(s);
          strcat(s, "\n");
          fputs(s, fp1);
          printf("\nDia chi : ");
          gets(s);
          strcat(s, "\n");
          fputs(s, fp1);
        }
      } while (strlen(s) > 0);
      fclose(fp1);
      fp1 = fopen(filename1, "r");
      while (fgets(s, 100, fp1) != NULL)
      {
        fgets(s1, 100, fp1);
        fgets(s2, 100, fp1);
        s[strlen(s)-1] = 0;
        s1[strlen(s1)-1] = 0;
        fprintf(fp2, "%s %s %s", s, s1, s2);
      }
      fclose(fp2);
    }
  }
}