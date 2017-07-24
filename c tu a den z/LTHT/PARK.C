/* Park dau doc dia cung */
#include <stdio.h>
#include <dos.h>

void main()
{
  int cyl;
  union REGS srv;

  srv.x.ax = 0x0800;
  srv.x.dx = 0x0080;

  /* Lay thong so tu o dia cung */

  if (int86 ( 0x13, &srv, &srv ) & 1 )
    abort ("\nKhong lay duoc tham so dia");

  srv.x.ax = 0x0c00;
  cyl = ((srv.x.cx & 0x00c0)<<2) | ((srv.x.cx & 0xff00)>>8);
  srv.x.dx = 0x0080;

  if (int86 ( 0x13, &srv, &srv ) & 1 )
    abort ("\nError = %02xh\n", (srv.x.ax & 0xff00)>>8);
  else
    printf("Dau doc dia C da nam tai cylinder %d\n", cyl);
}
