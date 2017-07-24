/* In chuoi theo cac tu, moi tu mot dong */
#include <stdio.h>

void main()
{
  char s[50];
  int i, len;

  printf("\nNhap vao mot chuoi : ");
  gets(s);
  len = strlen(s);
  i = 0;
  while (i<len)
  {
    while (s[i] == ' ' && i<len)
      i++;
    while (s[i] != ' ' && i<len)
      putc(s[i++], stdout);
    putc('\n', stdout);
  }
  getch();
}