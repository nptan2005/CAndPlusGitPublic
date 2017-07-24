/* Keyboard handle - Nhan F1 -> In ra cac ky tu ABC */
#include <stdio.h>
#include <dos.h>

#define KEYBOARD_PORT 0x60

extern unsigned _heaplen = 1024;
extern unsigned _stklen  = 512;

void far interrupt (*old_int9)();

void send_key(char ascii)
{
 asm {
	 mov ah,5
	 mov ch,0
	 mov cl,ascii
	 int 16h
  }
}
void far interrupt new_int9(void)
{
  unsigned char scancode, temp;

  scancode = inportb(KEYBOARD_PORT);

  if (scancode & 0x80)
  {
    old_int9();
  }
  else
  {
    switch(scancode)
    {
      case 0x3B : send_key('A');
                  send_key('B');
                  send_key('C');
                  break;
      default   : old_int9();
    }
  }
  outportb(0x20, 0x20);
}

void install_keyboard()
{
  old_int9 = getvect(9);
  setvect(9, new_int9);
}

void main()
{
  install_keyboard();
  keep(0, (_SS + (_SP/16) - _psp));
}