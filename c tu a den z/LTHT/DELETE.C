/* Xoa tap tin */
#include <stdio.h>
#include <dos.h>

void main(int argc, char *argv[])
{
  struct ffblk fblk;
  int done;

  if (argc < 2)
    printf("\nCach su dung : DELETE <ten tap tin can xoa>");
  else
  {
    done = findfirst(argv[1], &fblk, FA_ARCH);
    while (!done)
    {
      remove(fblk.ff_name);
      done = findnext(&fblk);
    }
    printf("\nCac tap tin %s da xoa xong!", argv[1]);
  }
  getch();
}