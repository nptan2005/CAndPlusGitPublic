#include <string.h>
#include <dos.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <io.h>

#define TRUE           (1)
#define FALSE          (0)
#define MAX_TABLE_SIZE (8*1024)
#define MIN_BLOCK_SIZE (1024)
#define cli()          __cli__()
#define sti()          __sti__()

typedef unsigned char byte;

void           do_main_task(void);
extern void    main_task(void);
extern void    _restorezero(void);

void interrupt (* old_intr_0x17)(void);
void interrupt (* old_intr_0x28)(void);

unsigned _heaplen = 1;
unsigned c_ss, c_sp;
unsigned save_ss, save_sp;

byte active = FALSE;  /* Co bao chuong trinh dang hoat dong */
byte wanted = FALSE;
byte far * dos_active;
byte print2disk = TRUE;

char file_name[128]="c:\\output.p2d"; /* File luu tru */
char table[MAX_TABLE_SIZE];
int  count=0;

void interrupt intr_0x17( unsigned bp, unsigned di, unsigned si,
                          unsigned ds, unsigned es, unsigned dx,
                          unsigned cx, unsigned bx, unsigned ax )
{
  sti();
  if ( print2disk )
  {
    ++active;
    cli();
    if (active == 1)
    {
      if (count > (MAX_TABLE_SIZE >> 1))
        if (! *dos_active){
          wanted = FALSE;
          sti();
          do_main_task();
          cli();
        }
        else wanted =  TRUE;
    }

    sti();
    while( active != 1 ) ;

    switch ( ax >> 8)
    {
      case 0:    table[count++] = (char) ax; break;
      case 1:    ax=0x9000; break;
      case 2:    ax=0x9000+(char)ax; break;
      case 0xFD: print2disk = TRUE; break;
      case 0xFE: print2disk = FALSE;
      case 0xFF: wanted = (count>0); break;
    }
    --active;
  }
  else
  {
    print2disk = ((ax >> 8) == 0xFD);
    _DX = dx; _BX = bx; _CX = cx; _AX = ax;
    (* old_intr_0x17)();
  }
}

void main_task(void)
{
  int hand = open(file_name, O_WRONLY|O_APPEND|O_CREAT, S_IREAD|S_IWRITE);
  if (hand > -1)
  {
    _write(hand, table, count);
    count=0;
    close(hand);
  }
}

void interrupt intr_0x28()
{
  (* old_intr_0x28)();
  sti();
  if (wanted || (count >= MIN_BLOCK_SIZE)){
    ++active;
    if ( active == 1)
    {
      wanted = FALSE;
      do_main_task();
    }
    --active;
  }
} /* intr_0x28 */


void do_main_task(void)
{
  cli();
  save_ss = _SS; save_sp = _SP;
  _SS = c_ss; _SP = c_sp;
  sti();
  main_task();
  cli();
  _SS = save_ss; _SP = save_sp;
  sti();
}


byte far * get_dos_flag(void)
{
  union  REGS  reg;
  struct SREGS s_reg;
  reg.x.ax = 0x3400;
  intdosx(&reg, &reg, &s_reg);
  return( MK_FP(s_reg.es, reg.x.bx) );
}


unsigned program_size(void){
    return(* ((unsigned far *) (MK_FP(_psp-1, 3))) );
}

main(int ac, char **av)
{
  if (ac > 1)
    strcpy( file_name, av[1] );

  c_ss = _SS; c_sp = _SP;
  dos_active = get_dos_flag();

  _restorezero();

  old_intr_0x28 = getvect(0x28);
  setvect( 0x28, intr_0x28 );

  old_intr_0x17 = getvect(0x17);
  setvect( 0x17, intr_0x17 );

  keep(0, program_size());
}
