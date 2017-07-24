#include <dos.h>

#define KEYBINT 0x9
#define KEYBPORT 0x60

#ifdef __cplusplus
    #define __CPPARGS ...
#else
    #define __CPPARGS
#endif

/* Giam luong hep va stack de cho chuong trinh chiem it bo nho */
extern unsigned _heaplen = 1024;
extern unsigned _stklen  = 512;

void interrupt ( *oldhandler)(__CPPARGS);
typedef unsigned int (far *s_arrayptr);

void interrupt handler(__CPPARGS)
{
  unsigned char key;

  key = inportb(KEYBPORT);
  if (key < 0x80)
    switch (key)
    {
      case 0x1D : /* phim Ctrl */
      case 0x2A : /* phim Left Shift */
      case 0x36 : /* phim Right Shift */
      case 0x38 : /* phim Alt */
      case 0x3A : /* phim Caps Lock */
      case 0x45 : /* phim Num Lock */
      case 0x46 : /* phim Scroll Lock */
                  asm {
                    pushf
                  }
                  break;
      default   : sound(1000);
                  delay(10);
                  nosound();
    }
  /* Goi thu tuc ngat cu */
  oldhandler();
}

void main(void)
{

  /* Lay dia chi cua ngat ban phim cu */
  oldhandler = getvect(KEYBINT);

  /* Dat ngat moi */
  setvect(KEYBINT, handler);

  /* Ket thuc va thuong tru trong bo nho */
  keep(0, (_SS + (_SP/16) - _psp));
}
