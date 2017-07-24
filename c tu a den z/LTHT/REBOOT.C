#define BOOT_SEG	0xffffL
#define BOOT_OFF	0x0000L
#define BOOT_ADR	((BOOT_SEG << 16) | BOOT_OFF)

#define DOS_SEG		0x0040L
#define RESET_FLAG	0x0072L
#define RESET_ADR	((DOS_SEG << 16) | RESET_FLAG)

void main()
{
	void ((far *fp)()) = (void (far *)()) BOOT_ADR;

	*(int far *)RESET_ADR = 0;
	(*fp)();
}
