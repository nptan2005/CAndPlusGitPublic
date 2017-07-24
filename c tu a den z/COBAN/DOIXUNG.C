/* Bai tap 9_4 - Tim chuoi doi xung */

void main()
{
  char chuoi[125];
  int i = 0, j;

  printf("\nNhap vao chuoi kiem tra : ");
  gets(chuoi);
  j = strlen(chuoi) - 1;

  while(chuoi[i++] == chuoi[j--])
  ;
  if (--i>=++j)
   printf("Chuoi doi xung");
  else
   printf("Chuoi khong doi xung");
  getch();
}