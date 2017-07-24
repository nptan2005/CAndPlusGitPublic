#include <dos.h>

#define ZERO_FLAG	0x040
#define CONTROL_C	3
#define MS_PER_TICK	53	/* So milliseconds cho moi lan goi ngat = 100 / 18.2 */

unsigned long count;
unsigned ticks;
void interrupt timer(), interrupt (*old_handler)();

main()
{
	union REGS sreg, rreg;

	count = 0;
	ticks = 0;

	sreg.x.dx = 0xff;
	sreg.h.ah = 0x06;

	printf("\nDe ngat chuong trinh, nhan to hop phim CTRL-C.");
	printf("\nDe hien len khoang thoi gian tu luc bat dau chuong trinh");
	printf("\nhay nhan mot phim bat ky. Don vi do la mili giay\n\n");

	old_handler = getvect(8);
	setvect(8, timer);

	/* Dat chip 8259 de cho phep ngat */
	outportb(0x21, inportb(0x21) & 0xfe);
  /* Gui lenh den 8253 - dat lai nhip */
	outportb(0x43, 0x34);

	/* Ngat thoi gian duoc dat goi 1 ms moi lan */
	outportb(0x40, 0xcd); /* Gui byte thap */
	outportb(0x40, 0x04); /* Gui byte cao */
	
	while (1)
  {
		while ( 1 )
    {
			intdos(&sreg, &rreg);
			if (!(rreg.x.flags & ZERO_FLAG) )
				break;
	  }

		if ( (rreg.x.ax & 0xff) == CONTROL_C )
    {
      /* Tra lai trang thai cu cho 8253 */
			outportb(0x43, 0x34);
			outportb(0x40, 0);
			outportb(0x40, 0);

			/* Tra lia ngat cu */
			setvect(8, old_handler);
			printf("Timer test program returning to MS-DOS.\n");
			exit(0);
		}
		else
			printf("TIME = %lu MSEC.\n",count);
	}
}

void interrupt timer()
{
	count++;

	if (++ticks == MS_PER_TICK)
  {
		old_handler();
		ticks = 0;
	}
	/* Bao ket thuc ngat cho chip 8259 */
	outportb(0x20, 0x20);
}
