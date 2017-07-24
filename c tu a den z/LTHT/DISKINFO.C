/* Bai tap 4_29 - Thong tin dia */
#include <conio.h>
#include <dos.h>

typedef unsigned char BYTE;
typedef unsigned WORD;

typedef struct tagdiskinfo {
  char signature;
  WORD skip;
  char vendor[8];
  WORD bytepersector;
  BYTE sectorpercluster;
  WORD reservedsectors;
  BYTE fatcopies;
  WORD rootentries;
  WORD totalsectors;
  BYTE media;
  WORD sectorperfat;
  WORD sectorpertrack;
  WORD heads;
  WORD hiddensectors;
  char loader [482];
} DISKINFO;

DISKINFO diskinfo;

void main(int argc, char *argv[])
{
  char disknum;

  if (argc < 2)
    printf("\nSu dung :\nDISKINFO <drive>");
  else
  {
    disknum = toupper(argv[1][0]) - 'A';
    if (absread(disknum, 1, 0, &diskinfo)!= 0)
      printf("Khong the doc boot record cua o %c", 'A' + disknum);
    else
    {
      printf("\n\n\nThong tin ve dia %c", 'A' + disknum);
      printf("\nSignature           = %c", diskinfo.signature);
      printf("\nBytes per Sector    = %d", diskinfo.bytepersector);
      printf("\nSectors per Cluster = %d", diskinfo.sectorpercluster);
      printf("\nReserved Sector     = %d", diskinfo.reservedsectors);
      printf("\nNum of FAT          = %d", diskinfo.fatcopies);
      printf("\nRoot Entries        = %d", diskinfo.rootentries);
      printf("\nTotal sectors       = %d", diskinfo.totalsectors);
      printf("\nMedia Descriptor    = %d", diskinfo.media);
      printf("\nSectors per FAT     = %d", diskinfo.sectorperfat);
      printf("\nSectors per Track   = %d", diskinfo.sectorpertrack);
      printf("\nNum of Head         = %d", diskinfo.heads);
      printf("\nHidden sectors      = %d", diskinfo.hiddensectors);
    }
  }
  getch();
}