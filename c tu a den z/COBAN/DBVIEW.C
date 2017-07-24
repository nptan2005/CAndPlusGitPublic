/* Baitap 1_69 - Xem tap tin DBF */
#include <stdio.h>

typedef struct tagDBF_HEADER {
	unsigned char signature;	/* 03 = dbf, 83 dbf+dbt */
	unsigned char ymd[3];
	long num_records;
	int data_off;
	int rec_size;
	unsigned char pad[20];
} DBF_HEADER;

typedef struct tagDBF_STRUCT {
	char name[11];
	char type;
  long fstart;
  unsigned char fsize;
  unsigned char decimal;
	char pad[14];
} DBF_STRUCT;

DBF_HEADER dbheader;
DBF_STRUCT dbstruct[255];
int numfields;

void main()
{
  char filename[50];
  char *dump, chuoi[250] ;
  int i, j, offset, k;
  FILE *fp;

  printf("\nCho biet ten tap tin DBF muon xem : ");
  gets(filename);
  if ((fp=fopen(filename, "rb")) == NULL)
    printf("Khong the mo tap tin %s", filename);
  else
  {
    fread(&dbheader, sizeof(DBF_HEADER), 1, fp);
    if (dbheader.signature == 3 || dbheader.signature == 0x83)
    {
      numfields = (dbheader.data_off - 33) / 32;
      fread(&dbstruct, sizeof(DBF_STRUCT), numfields, fp);
      fgetc(fp);
      dump = (char *)malloc(dbheader.rec_size);
      k = 7;
      for (j=0; j<numfields; j++)
      {
        gotoxy(k, wherey());
        textcolor(j+1);
        cprintf("%s", dbstruct[j].name);
        k += dbstruct[j].fsize;
      }
      for (i=0; i<dbheader.num_records; i++)
      {
        fread(dump, dbheader.rec_size, 1, fp);
        printf("\n%3d ", i+1);
        if (dump[0] != 32)
          printf("* ");
        else
          printf("  ");
        offset= 1;
        for (j=0; j<numfields; j++)
        {
          switch(dbstruct[j].type)
          {
             case 'C' :  strncpy(chuoi, &dump[offset], dbstruct[j].fsize);
                         chuoi[dbstruct[j].fsize] = 0;
                         printf("%s ", chuoi);
                         break;
             case 'D' :  printf("%c%c/%c%c/%c%c%c%c ",dump[offset+6], dump[offset+7],
                                dump[offset+4],dump[offset+5],dump[offset],dump[offset+1],
                                dump[offset+2],dump[offset+3]);
                         break;
             case 'N' :  for (k=0; k<dbstruct[j].fsize; k++)
                           printf("%c", dump[offset+k]);
                         printf(" ");
                         break;
             case 'L' :  printf("%c ", dump[offset]);
                         break;
          }
          offset += dbstruct[j].fsize;
        }
      }
      free(dump);
    }
    else
      printf("Khong phai tap tin DBF");
    fclose(fp);
  }
  getch();
}