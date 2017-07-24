/* Hien thuoc tinh cua tap tin */
#include <dos.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define NULL 0

#define  MSDOSS   0x0021
#define  SETMODE  0x4301
#define  GETMODE  0x4300
#define  SEARCHF  0x4e00
#define  SEARCHN  0x4f00
#define  SETDMA   0x1a00
#define  CONNIO   0x06
#define  CARRYF   0x0001
#define  ZEROF    0x0040

/* Thuoc tinh file */
#define  RO       0x0001
#define  HIDDEN   0x0002
#define  SYSTEM   0x0004
#define  VOLUME   0x0008
#define  SUBDIR   0x0010

/* Cac ma loi */
#define  NOFILE   0x0002   /* file not found */
#define  NOPATH   0x0003   /* path not found */
#define  NOACCESS 0x0005   /* access denied */
#define  NOFILES  0x0012   /* no more files on SEARCHN */

/* Cac chuc nang BIOS */
#define  CURR_VIDEO  0x0f
#define  READ_CURSOR 0x03
#define  SET_CURSOR  0x02
#define  VIDEO_INT   0x0010

struct DMA {
   char reserved[21];
   char attribute;
   unsigned time;
   unsigned date;
   unsigned size_L;
   unsigned size_h;
   char fname[13];
};

union REGS inregs, outregs;
struct SREGS segregs;

void echo(unsigned char ch)
{
  inregs.h.ah = CONNIO;
  inregs.h.dl = ch;
  int86(MSDOSS, &inregs, &outregs);
}

void fpe(char *string)
{
  static unsigned char ch, ch1;
  void echo();
  char input();

  while (( ch = *string++) != (unsigned char) NULL)
    if (ch != '\n')
      echo(ch);
    else
    {
       echo('\015');        /* ASCII CR */
       echo(ch);            /* now do linefeed */
    }
    if ((ch1 = input()) != (unsigned char) NULL)
      if (ch1 == 3)
        exit(1);
      else while ((ch1 = input()) == (unsigned char) NULL)
        if (ch1 == 3)
          exit(1);
}

void cursor_col(int col)
{
  static unsigned char current_page;

  inregs.h.ah = CURR_VIDEO;     /* Get current page funct */
  int86(VIDEO_INT, &inregs, &outregs);
  current_page = outregs.h.bh;

  inregs.h.ah = READ_CURSOR;    /* Read cur pos funct call */
  inregs.h.bh = current_page;   /* Page number */
  int86(VIDEO_INT, &inregs, &outregs);

  inregs.h.ah = SET_CURSOR;     /* Set cur pos funct call */
  inregs.h.bh = current_page;   /* Page number */
  inregs.h.dh = outregs.h.dh;   /* row (y) from fumct 3 above */
  inregs.h.dl = outregs.h.dl;   /* col (x) from funct 3 above */
  int86(VIDEO_INT, &inregs, &outregs);
}

void concat(char *cnew, char *first, char *second)
{

   while(*first != (char) NULL) {
      *cnew = *first;
      first++;
      cnew++;
   }
   while(*second != (char) NULL) {
      *cnew = *second;
      second++;
      cnew++;
   }
   *cnew = (char) NULL;
}

char lastchar(char *string)
{
   return string[(strlen(string) - 1)];
}

int getpath(char *argvs, char *path)
{
  static char ch;
  register int i;
  int bslpos = -1;

  for(i = 0; (ch = argvs[i]) != (char) NULL; i++)
  {
    if (ch == '\\' || ch == ':')
      bslpos = i;
  }
  if (bslpos != -1)
    for(i = 0; i <= bslpos; i++)
      path[i] = argvs[i];
  path[i] = NULL;
  return bslpos;
}

void pfname(char *path, char *fname, int bslpos)
{
  register i, j;
  static char ch;

  j = bslpos != -1 ? bslpos + 1 : 0;
  for (i = 0; (ch = fname[i]) != (char) NULL; i++, j++)
    path[j] = fname[i];
  path[j] = (char) NULL;
}

void display_type(char att)
{
  cursor_col(30);
  if ((att & 0x1f) == 0)
    fpe(" NORMAL");
  else
  {
    if ((att & RO) == RO)
      fpe(" READ/ONLY");
    if ((att & HIDDEN) == HIDDEN)
      fpe(" HIDDEN");
    if ((att & SYSTEM) == SYSTEM)
      fpe(" SYSTEM");
    if ((att & VOLUME) == VOLUME)
      fpe(" VOLUME");
    if ((att & SUBDIR) == SUBDIR)
      fpe(" SUB-DIRECTORY");
  }
}

char input()
{
  static unsigned int zerof;    /* used for return of zero flag */
  extern int getzf();

  inregs.h.ah = CONNIO;              /* AH = funct 06h */
  inregs.h.dl = 0xff;           /* input subfunction */
  int86x(MSDOSS, &inregs, &outregs, &segregs);
  zerof = getzf();        /* ASM routine to get zero flag */

  if ((zerof & ZEROF) == ZEROF)
      return (char) NULL;
   else
      return outregs.h.al;
}

void main(int argc, char *argv[])
{
  char path[64];
  char atton_off;
  char new_arg[64];
  int bslpos;
  struct DMA dmabuf;
  int i;
  int carryf;

  void fpe(), bad_syntax(), pfname();
  void set_att_masks(), change_att();
  void concat();
  void display_type();
  char lastchar();
  int getpath();

  unsigned att_on_mask, att_off_mask;
  unsigned ask;
  int start_file;
  int display_att_only;

  if (argc < 2)
    bad_syntax();
  atton_off = argv[1][0];
  if (atton_off != '+' && atton_off != '-')
  {
    start_file = 1;
    display_att_only = TRUE;
  }
  else
  {
    start_file = 2;               /* argv[1] is control parameter */
    display_att_only = FALSE;     /* and argv[2] starts files */
    if (argc < 3)                 /* must have at least one file */
      bad_syntax();
    set_att_masks(argv[1], &att_on_mask, &att_off_mask, &ask);
  }

  segread(&segregs);      /* put seg regs in structure (need DS) */
  inregs.x.ax = SETDMA;              /* AH = funct 1Ah */
  inregs.x.dx = (unsigned) &dmabuf;
  int86x(MSDOSS, &inregs, &outregs, &segregs);

  for(i = start_file; i < argc; i++)
  {
    if (lastchar(argv[i]) == ':')
    {
      concat(new_arg, argv[i], "\\*.*");
      argv[i] = new_arg;
    }
    else
      if (lastchar(argv[i]) == '\\')
      {
        concat(new_arg, argv[i], "*.*");
        argv[i] = new_arg;
      }
      else
      {
        segread(&segregs);      /* put seg regs in structure (need DS) */
        inregs.x.ax = GETMODE;  /* AX = 4300 (Int 43h, 00 = 'get' mode */
        inregs.x.dx = (unsigned) argv[i];
        int86x(MSDOSS, &inregs, &outregs, &segregs);
        carryf = outregs.x.cflag;
         if(outregs.x.cx == SUBDIR)
         {
           concat(new_arg, argv[i], "\\*.*");
           argv[i] = new_arg;
         }
       }
     bslpos = getpath(argv[i], path);

     fpe("\n====================> ");
     fpe(" >====================\n\n");

     segread(&segregs);      /* put seg regs in structure (need DS) */
     inregs.x.ax = SEARCHF;             /* AH = funct 4Eh */
     inregs.x.dx = (unsigned) argv[i];
     inregs.x.cx = 0x001f;              /* search for file with any attri- */
     int86x(MSDOSS, &inregs, &outregs, &segregs);  /* bute except archive */
     carryf = outregs.x.cflag;
     if ((carryf & CARRYF) == CARRYF)
     {
       if ((outregs.x.ax == NOFILES) || (outregs.x.ax == NOPATH ))
       {
         fpe("\n");
         fpe(argv[i]);
         fpe(" not found\n\n\r");
       }
       else
       {
         fpe("\nUndefined error\n\007");
         exit(1);
       }
     }
     while((carryf & CARRYF) != CARRYF)
     {
       pfname(path, &(dmabuf.fname[0]), bslpos);
       fpe(path);     /* echo path and/or file */
       display_type(dmabuf.attribute);        /* echo current attribs */
       if ((display_att_only != TRUE) && (dmabuf.attribute != SUBDIR))
         change_att(path, dmabuf.attribute, &att_on_mask,&att_off_mask,&ask);
       else
         fpe("\n");

       segread(&segregs);      /* put seg regs in structure (need DS) */
       inregs.x.ax = SEARCHN;  /* AX = 4F00 (4Fh= 'search for next match' */
       int86x(MSDOSS, &inregs, &outregs, &segregs);
       carryf = outregs.x.cflag;
     }
   }        /* end of for loop */
   exit(0);
}

