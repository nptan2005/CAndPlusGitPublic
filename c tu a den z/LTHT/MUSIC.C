#include <stdio.h>
#include <dos.h>

#define INTR 0X1C    /* Ngat dong ho */

#ifdef __cplusplus
    #define __CPPARGS ...
#else
    #define __CPPARGS
#endif

extern unsigned _heaplen = 1024*8;
extern unsigned _stklen  = 1024*4;

typedef struct tagMUSIC {
  unsigned int node;  /* Tan so - not nhac */
  unsigned int ngung; /* Tinh theo chu ky clock */
} MUSIC;

MUSIC bannhac[1000];

void interrupt ( *oldhandler)(__CPPARGS);

int count=0;
int num_node;
int cur_node = 0;

void interrupt handler(__CPPARGS)
{
  if (count == 0)
    sound(bannhac[cur_node].node);
  count++;
  if (count >= bannhac[cur_node].ngung)
  {
    nosound();
    count = 0;
    cur_node++;
    if (cur_node >= num_node)
      cur_node = 0;
  }
  oldhandler();
}

void main(int argc, char *argv[])
{
  FILE *fp;
  int i;

  if (argc < 2)
  {
    printf("\n\nCach dung : MUSIC <tap tin nhac>");
    return;
  }
  if ((fp = fopen(argv[1], "rt")) == NULL)
  {
    printf("\n\nKhong the mo tap tin %s", argv[1]);
    return;
  }
  fscanf(fp, "%u", &num_node);
  if (num_node > 1000)
    num_node = 1000;
  for (i=0; i<num_node; i++)
    fscanf(fp, "%u %u", &(bannhac[i].node), &(bannhac[i].ngung));
  fclose(fp);

  cur_node = 0;
  oldhandler = getvect(INTR);
  setvect(INTR, handler);

  keep(0, (_SS + (_SP/16) - _psp));
}
