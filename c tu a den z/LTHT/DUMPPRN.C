/* Bai tap 4_31 - Dump noi dung tap tin ra may in theo dang hex */
#include <stdio.h>
#include <conio.h>
#include <dos.h>

#define MAX 256

long fsize(FILE *stream);

unsigned char buffer[MAX];
long filesize, offset;
char HEX[16] = "0123456789ABCDEF";

void HexWord (unsigned n, char *s)
{
  int i;
  for (i=3; i>=0; i--)
  {
     s[i] = HEX[n%16];
     n /= 16;
  }
  s[4] = 0;
}

void HexByte (unsigned char n, char *s)
{
  int i;
  for (i=1; i>=0; i--)
  {
     s[i] = HEX[n%16];
     n /= 16;
  }
  s[2] = 0;
}

void writebuf()
{
  char sseg[5], sofs[5], sbyte[3];
  unsigned seg, ofs;
  int i, j;

  clrscr();
  for (i=0; i<16; i++)
  {
    seg = (offset + (long)i*16) / 0xFFFF;
    ofs = (offset + (long)i*16) % 0xFFFF;
    HexWord(seg, sseg);
    HexWord(ofs, sofs);
    fprintf(stdprn, "\n%s:%s  ", sseg, sofs);
    for (j=0; j<16; j++)
    {
      HexByte(buffer[i*16 + j], sbyte);
      fprintf(stdprn, "%s ", sbyte);
      if (j == 8)
        fprintf(stdprn, "- ");
    }
    fprintf(stdprn, "  ");
    for (j=0; j<16; j++)
      if (buffer[i*16+j] >=32)
        fprintf(stdprn, "%c", buffer[i*16+j]);
      else
        fprintf(stdprn, ".");
  }
}

void main(int argc, char *argv[])
{
  char c;
  FILE *fp;

  if (argc < 2)
  {
    printf("\nCach su dung : DUMPPRN <tap tin>");
    exit(1);
  }
  if ((fp = fopen(argv[1],"rb")) == NULL)
  {
    printf("\nKhong the mo tap tin %s.", argv[1]);
    exit(1);
  }
  filesize = fsize(fp);
  offset = 0;
  memset(buffer, 0, 256);
  fread(&buffer, sizeof buffer, 1, fp);
  writebuf();
  do {
    offset += 256;
    fseek(fp, offset, SEEK_SET);
    memset(buffer, 0, 256);
    fread(&buffer, sizeof buffer, 1, fp);
    writebuf();
  } while ((offset + (long)256) < filesize);
  fclose(fp);
}

long fsize(FILE *stream)
{
   long curpos, length;

   curpos = ftell(stream);
   fseek(stream, 0L, SEEK_END);
   length = ftell(stream);
   fseek(stream, curpos, SEEK_SET);
   return length;
}
