/* Bai tap 1_95 - Tim va thay the mot chuoi con */
/*
  Tim kiem va thay the chuoi con trong mot chuoi lon
  s  : chuoi lon
  s1 : chuoi con
  s2 : chuoi se thay the
  De chac chan khong bi loi thi chuoi s phai co kha nang chua du
*/
#include <stdio.h>
#include <string.h>
char *str_str(char *s, char *s1, char *s2)
{
  int len  = strlen(s);
  int len1 = strlen(s1);
  int len2 = strlen(s2);
  int i=0, j, luu;

  if (len1!=0)
    while (i<len)
    {
      if (s[i] == s1[0])
      {
        j = 0;
        luu = i;
        while ((s[luu++] == s1[j++]) && (j < len1)) ;
        if (j==len1)
        {
          memmove(&s[i+len2], &s[i+len1], len - i - len1+1);
          memcpy(&s[i],s2,len2);
          len = len + len2 - len1;
          i += len2;
        }
        else i ++;
      }
      else i++;
    }
  return s;
}

void main()
{
  char s[255], s1[20], s2[20];

  printf("Nhap vao chuoi lon : "); gets(s);
  printf("Nhap vao chuoi tim : "); gets(s1);
  printf("Nhap vao chuoi thay the : "); gets(s2);
  str_str(s, s1, s2);
  printf("Chuoi sau khi tim va thay the la : %s", s);
  getch();
}