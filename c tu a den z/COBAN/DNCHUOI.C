/* Dao nguoc chuoi */

char *dnchuoi(char *s)
{
  char *tmp, i;

  i = 0;
  tmp = (char *)malloc(strlen(s)+1);
  while (i<strlen(s))
    *(tmp+i) = *(s + strlen(s) - i++ - 1);
  *(tmp+i) = 0;
  return tmp;
}

void main()
{
  char hello[] = "Hello World";
  char *s;

  printf("\nChuoi ban dau = %s", hello);
  s = dnchuoi(hello);
  printf("\nChuoi dao nguoc = %s", s);
  getch();
}