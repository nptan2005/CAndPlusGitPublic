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

int menu()
{
  char c;
  clrscr();
  printf("+----- Menu -----+");
  printf("\n+----------------+");
  printf("\n+ 1. Nhap        +");
  printf("\n+ 2. Xoa         +");
  printf("\n+ 3. Sua doi     +");
  printf("\n+ 4. Liet ke     +");
  printf("\n+----------------+");
  printf("\n+ 5. Luu len dia +");
  printf("\n+ 6. Lay tu dia  +");
  printf("\n+----------------+");
  printf("\n+ 0. Thoat       +");
  printf("\n+----------------+");
  printf("\nChon muc : ");
  do {
    c = getch();
  } while (c<'0' || c>'6');
  return c-'0';
}

void nhapmoi()
{
  int done = 0;
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
}

void xoa()
{
  int i, done = 0, found, dump[MAX];
  char hoten[35], hotentmp[35];

  while (!done)
  {
    if (numrecords != 0)
    {
      printf("\nHo ten hoc sinh can xoa (trong de thoat) : ");
      gets(hoten);
      if (strlen(hoten) == 0)
        done = 1;
      else
      {
        i = found = 0;
        do {
           strcpy(hotentmp,danhsach[i].hoten);
          if (strcmp(strupr(hoten), strupr(hotentmp)) == 0)
            dump[found++] = i;
          i++;
        } while (i<numrecords);
        if (!found)
          printf("\nKhong tim thay hoc sinh co ten %s", hoten);
        else
        {
          for (i=0; i<found; i++)
          {
            printf("\n%3d %-35s %-7s %4.1f %4.1f %4.1f", i+1, danhsach[dump[i]].hoten,danhsach[dump[i]].lop,
             danhsach[dump[i]].diemtoan, danhsach[dump[i]].diemly, danhsach[dump[i]].diemhoa);
          }
          printf("\n\nTim thay %d hoc sinh.", found);
          printf("\nChon thu tu muon xoa (neu muon huy bo thi chon so khong nam trong pham vi): ");
          scanf("%d", &i);
          if (i >= 1 && i <= found)
          {
            for (found=dump[i-1]; found<numrecords-1; found++)
              danhsach[found] = danhsach[found+1];
            numrecords--;
            printf("\nDa huy");
          }
          else
            printf("\nViec xoa bi huy bo.");
        }
        done = 1;
      }
      getch();
    }
    else
      done = 1;
  }
}

void sua()
{
  int i, done = 0, found, dump[MAX];
  char hoten[35], hotentmp[35];
  float diem;

  while (!done)
  {
    if (numrecords != 0)
    {
      printf("\nHo ten hoc sinh can sua (trong de thoat) : ");
      gets(hoten);
      if (strlen(hoten) == 0)
        done = 1;
      else
      {
        i = found = 0;
        do {
           strcpy(hotentmp,danhsach[i].hoten);
          if (strcmp(strupr(hoten), strupr(hotentmp)) == 0)
            dump[found++] = i;
          i++;
        } while (i<numrecords);
        if (!found)
          printf("\nKhong tim thay hoc sinh co ten %s", hoten);
        else
        {
          for (i=0; i<found; i++)
          {
            printf("\n%3d %-35s %-7s %4.1f %4.1f %4.1f", i+1, danhsach[dump[i]].hoten,danhsach[dump[i]].lop,
             danhsach[dump[i]].diemtoan, danhsach[dump[i]].diemly, danhsach[dump[i]].diemhoa);
          }
          printf("\n\nTim thay %d hoc sinh.", found);
          printf("\nChon thu tu muon sua doi (neu muon huy bo thi chon so khong nam trong pham vi): ");
          scanf("%d%*c", &i);
          if (i >= 1 && i <= found)
          {
            printf("\n%s\nHo ten : ", danhsach[dump[i-1]].hoten);
            gets(danhsach[dump[i-1]].hoten);
            printf("\n%s\nLop : ", danhsach[dump[i-1]].lop);
            gets(danhsach[dump[i-1]].lop);
            printf("\n%4.2f\nDiem toan : ",danhsach[dump[i-1]].diemtoan);
            scanf("%f", &diem);
            danhsach[dump[i-1]].diemtoan = diem;
            printf("\n%4.2f\nDiem ly : ", danhsach[dump[i-1]].diemly);
            scanf("%f", &diem);
            danhsach[dump[i-1]].diemly = diem;
            printf("\n%4.2f\nDiem hoa : ", danhsach[dump[i-1]].diemhoa);
            scanf("%f%*c", &diem);
            danhsach[dump[i-1]].diemhoa = diem;
            printf("\nDa thay doi");
          }
          else
            printf("\nViec thay doi bi huy bo.");
        }
        done = 1;
      }
      getch();
    }
    else
      done = 1;
  }
}

void lietke()
{
  int i;

  if (numrecords != 0)
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

void getdata()
{
  char c;
  int start, nrec;
  FILE *fp;
  long curpos, length;

  start = 0;
  if (numrecords != 0)
  {
    printf("\nDang co du lieu trong bo nho. Co muon noi them vao khong?(C/K)");
    c = toupper(getch());
    if (c == 'C')
      start = numrecords;
    else
      start = 0;
  }
  if ((fp = fopen(filename, "r")) == NULL)
    printf("\nKhong the mo tap tin %s", filename);
  else
  {
    curpos = ftell(fp);
    fseek(fp, 0L, SEEK_END);
    length = ftell(fp);
    fseek(fp, curpos, SEEK_SET);
    nrec = length / sizeof(HOCSINH);
    fread(&danhsach[start], sizeof(HOCSINH), nrec, fp);
    fclose(fp);
    printf("\nThem vao %d records.", nrec);
    numrecords = numrecords + nrec;
    getch();
  }
}

void putdata()
{
  FILE *fp;

  if ((fp = fopen(filename, "w+")) == NULL)
    printf("\nKhong thay ghi tap tin %s", filename);
  else
  {
    fwrite(&danhsach[0], sizeof(HOCSINH), numrecords, fp);
    fclose(fp);
    printf("\nGhi %d records.", numrecords);
    getch();
  }
}

void main()
{
  int chon, done = 0;

  do {
    chon = menu();
    switch(chon)
    {
      case 1 : nhapmoi();
               break;
      case 2 : xoa();
               break;
      case 3 : sua();
               break;
      case 4 : lietke();
               break;
      case 5 : putdata();
               break;
      case 6 : getdata();
               break;
      case 0 : done = 1;
    }
  } while (!done);
}
