/* Bai tap 1_61 - Quan ly danh sach hoc sinh */
#include <stdio.h>

#define MAX 100

typedef struct hocsinh {
  char hoten[35];
  char lop[7];
  float diemtoan, diemly, diemhoa;
} HOCSINH;

HOCSINH danhsach[MAX];
int numrecords = 0;
char filename[] = "DANHSACH.DAT";

void main()
{
  int done = 0, i;
  char hoten[35];
  float diem;

  do {
    printf("\nHo ten (trong de thoat) : ");
    gets(hoten);
    if (strlen(hoten) == 0)
      done = 1;
    else
    {
      strcpy(danhsach[numrecords].hoten, hoten);
      printf("\nLop : ");
      gets(danhsach[numrecords].lop);
      printf("\nDiem toan : ");
      scanf("%f", &diem);
      danhsach[numrecords].diemtoan = diem;
      printf("\nDiem ly : ");
      scanf("%f", &diem);
      danhsach[numrecords].diemly = diem;
      printf("\nDiem hoa : ");
      scanf("%f%*c", &diem);
      danhsach[numrecords].diemhoa = diem;
      numrecords++;
    }
  } while (!done);

  for (i=0; i<numrecords; i++)
  {
    printf("\n+-----+------------------------------------+--------+------+------+------+");
    printf("\n| STT |         H O   V A   T E N          |  L O P | TOAN |  LY  |  HOA |");
    printf("\n+-----+------------------------------------+--------+------+------+------+");
    for (i=0; i<numrecords; i++)
    {
      printf("\n| %3d | ", i+1);
      printf("%-35s| %-7s| %4.1f | %4.1f | %4.1f |", danhsach[i].hoten,danhsach[i].lop,
             danhsach[i].diemtoan, danhsach[i].diemly, danhsach[i].diemhoa);
    }
    printf("\n+-----+------------------------------------+--------+------+------+------+");
  }
  getch();
}
