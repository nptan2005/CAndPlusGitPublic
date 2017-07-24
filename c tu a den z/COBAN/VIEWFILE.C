/* Xem tap tin cho phep cuon */
#include <stdio.h>
#include <conio.h>

void main()
{
  FILE *fp;
  char filename[50], s[255], *hang[1000], c;
  int nline = 0, line = 0, i;

  printf("\nNhap ten tap tin muon xem : ");
  gets(filename);
  if ((fp = fopen(filename,"r")) == NULL)
    printf("\nKhong the mo tap tin %s", filename);
  else
  {
    while (!feof(fp))
    {
      fgets(s, 255, fp);
      hang[nline] = (char *)malloc(strlen(s));
      strcpy(hang[nline], s+1);
      nline++;
    }
    do {
      clrscr();
      i = line;
      while (i<line+26 && i<nline)
        printf("%s", hang[i++]);
      c = getch();
      if (c == 0)
      {
        c = getch();
        switch(c)
        {
          case 72 : if (line > 0)
                      line--;
                    break;
          case 80 : if (line+25 < nline)
                      line++;
                    break;
        }
      }
    } while (c != 27);
    fclose(fp);
  }
}