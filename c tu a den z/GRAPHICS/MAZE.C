#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>
#include <alloc.h>

#define TRUE 1
#define FALSE 0

typedef struct stack_1_rec {
  unsigned char      index_1;
  struct stack_1_rec *next_ptr;
} *stack_1_rec_ptr;

typedef struct stack_2_rec {
  unsigned char      index_1;
  unsigned char      index_2;
  struct stack_2_rec *next_ptr;
} *stack_2_rec_ptr;

static void generate_maze(int *,int *,int *,int *,int *,int *,int *,
             int *,int *,int *,int *,int *,int *,int *,int *);
static void initialize(int *,int *,int *,int *,int *,int *,int *,int *,
             int *,int *,int *,int *,int *,int *,int *,int *);
static void let_user_try_to_solve(int *,int *,int *,int *,int *,int *,
             int *,int *,int *,int *,int *);
void main(void);
static void optionally_have_computer_solve(int *,int *,int *,int *,
             int *,int *,int *,int *,int *);
static void remove_rejected_attempts(int *,int *,int *,int *,
             stack_1_rec_ptr *,stack_1_rec_ptr *,int *,int *,int *,
             int *,int *);

void main()
  {
    int delta_x [4] [24];
    int delta_y [4] [24];
    int erase;
    int fatal_error;
    int key_pressed;
    int magnitude_delta_x;
    int magnitude_delta_y;
    int num_columns;
    int num_rows;
    int passage;
    int path;
    int r_n [8];
    int twice_magnitude_delta_x;
    int twice_magnitude_delta_y;
    int wall;
    int x_max;
    int y_max;

    fatal_error=FALSE;

    initialize(&delta_x[0][0],&delta_y[0][0],&erase,&fatal_error,
    &magnitude_delta_x,&magnitude_delta_y,&num_columns,&num_rows,
    &passage,&path,&r_n[0],&twice_magnitude_delta_x,
    &twice_magnitude_delta_y,&wall,&x_max,&y_max);
    if (! fatal_error)
      generate_maze(&delta_x[0][0],&delta_y[0][0],&magnitude_delta_x,
       &magnitude_delta_y,&num_columns,&num_rows,&passage,&path,
       &r_n[0],&twice_magnitude_delta_x,&twice_magnitude_delta_y,
       &wall,&x_max,&y_max,&fatal_error);
    if (! fatal_error)
      let_user_try_to_solve(&delta_x[0][0],&delta_y[0][0],&erase,
       &key_pressed,&magnitude_delta_x,&magnitude_delta_y,&passage,
       &path,&wall,&y_max,&fatal_error);
    if (! fatal_error)
      optionally_have_computer_solve(&delta_x[0][0],&delta_y[0][0],
       &key_pressed,&magnitude_delta_x,&magnitude_delta_y,&passage,
       &path,&y_max,&fatal_error);
    if (! fatal_error)
      closegraph();
    return;
}

static void initialize(delta_x,delta_y,erase,fatal_error,
 magnitude_delta_x,magnitude_delta_y,num_columns,num_rows,passage,path,
 r_n,twice_magnitude_delta_x,twice_magnitude_delta_y,wall,x_max,y_max)
  int *delta_x;
  int *delta_y;
  int *erase;
  int *fatal_error;
  int *magnitude_delta_x;
  int *magnitude_delta_y;
  int *num_columns;
  int *num_rows;
  int *passage;
  int *path;
  int *r_n;
  int *twice_magnitude_delta_x;
  int *twice_magnitude_delta_y;
  int *wall;
  int *x_max;
  int *y_max;
    {
      int  delta_index_1a;
      int  delta_index_1b;
      int  delta_index_1c;
      int  delta_index_1d;
      int  delta_index_2;
      int  ErrorCode;
      int  GraphDriver;
      int  GraphMode;
      int  max_num_columns;
      int  max_num_rows;
      int  max_x;
      int  max_y;
      int  r_n_index_1;
      int  r_n_index_2;
      char seed [256];
      int  tem_int;

      detectgraph(&GraphDriver,&GraphMode);
      ErrorCode=graphresult();
      if (ErrorCode != 0)
        {
          *fatal_error=TRUE;
          printf("Fatal error:  %s\n",grapherrormsg(ErrorCode));
        }
      if (! *fatal_error)
        {
          switch (GraphDriver)
            {
              case CGA:
              case MCGA:
              case ATT400:
                {
                  GraphMode=0;
                  *erase=2;
                  *wall=1;
                  *passage=0;
                  *path=3;
                  break;
                }
              case EGA:
                {
                  GraphMode=EGAHI;
                  *erase=4;
                  *wall=9;
                  *passage=0;
                  *path=2;
                  break;
                }
              case EGA64:
                {
                  GraphMode=EGA64HI;
                  *erase=2;
                  *wall=1;
                  *passage=0;
                  *path=3;
                  break;
                }
              case VGA:
                {
                  GraphMode=VGAHI;
                  *erase=4;
                  *wall=9;
                  *passage=0;
                  *path=2;
                  break;
                }
              case IBM8514:
                {
                  GraphMode=IBM8514HI;
                  *erase=4;
                  *wall=9;
                  *passage=0;
                  *path=2;
                  break;
                }
              default:
                {
                  GraphMode=0;
                  *erase=0;
                  *wall=1;
                  *passage=0;
                  *path=1;
                  break;
                }
            }
          initgraph(&GraphDriver,&GraphMode,"");
          ErrorCode=graphresult();
          if (ErrorCode == 0)
            {
              max_x=getmaxx();
              max_y=getmaxy();
              max_num_columns=max_x/2;
              max_num_rows=max_y/2;
              closegraph();
            }
          else
            {
              GraphDriver=DETECT;
              initgraph(&GraphDriver,&GraphMode,"");
              ErrorCode=graphresult();
              if (ErrorCode == 0)
                {
                  max_x=getmaxx();
                  max_y=getmaxy();
                  max_num_columns=max_x/2;
                  max_num_rows=max_y/2;
                  *erase=0;
                  *wall=1;
                  *passage=0;
                  *path=1;
                  closegraph();
                }
              else
                {
                  *fatal_error=TRUE;
                  printf("Fatal error:  %s\n",grapherrormsg(ErrorCode));
                }
            }
        }
      if (! *fatal_error)
        {
          printf("                                 Maze Generator\n");
          printf("\n");
          printf("\n");
          printf("\n");
          printf(
"     This program will generate a maze.  After the maze is generated, you");
          printf("\n");
          printf(
"may use the cursor keys to solve it.  Press Q to quit or S to have the");
          printf("\n");
          printf(
"computer solve the maze.  If the computer solves the maze, you must press");
          printf("\n");
          printf(
"some key to exit.\n");
          printf("\n");
          do
            {
              printf("     Number of columns (2 to ");
              printf("%d",max_num_columns);
              printf(")? ");
              fflush(stdin);
              scanf("%d",num_columns);
              if ((*num_columns < 2)
              ||  (*num_columns > max_num_columns))
                {
                  printf(
                   "? The number of columns must be between 2 and ");
                  printf("%d",max_num_columns);
                  printf(", inclusively\n");
                }
            }
          while ((*num_columns < 2)
          ||     (*num_columns > max_num_columns));
          printf("\n");
          do
            {
              printf("     Number of rows (2 to ");
              printf("%d",max_num_rows);
              printf(")? ");
              fflush(stdin);
              scanf("%d",num_rows);
              if ((*num_rows < 2) || (*num_rows > max_num_rows))
                {
                  printf(
                   "? The number of rows must be between 2 and ");
                  printf("%d",max_num_rows);
                  printf(", inclusively\n");
                }
            }
          while ((*num_rows < 2) || (*num_rows > max_num_rows));
          printf("\n");
          printf("     Random number seed? ");
          fflush(stdin);
          gets(&seed[0]);
          for (r_n_index_1=0;
           ((r_n_index_1 < 8) && (seed[r_n_index_1] != (char) 0));
           r_n_index_1++)
            {
              tem_int=(int) seed[r_n_index_1];
              while (tem_int >= 29) tem_int-=29;
              *(r_n+r_n_index_1)=tem_int;
            }
          r_n_index_2=7;
          while (r_n_index_1 > 0)
            {
              r_n_index_1--;
              *(r_n+r_n_index_2)=*(r_n+r_n_index_1);
              r_n_index_2--;
            }
          while (r_n_index_2 >= 0)
            {
              *(r_n+r_n_index_2)=19;
              r_n_index_2--;
            }
          initgraph(&GraphDriver,&GraphMode,"");
          *magnitude_delta_x=max_x/(*num_columns)/2;
          *twice_magnitude_delta_x
           =(*magnitude_delta_x)+(*magnitude_delta_x);
          *magnitude_delta_y=max_y/(*num_rows)/2;
          *twice_magnitude_delta_y
           =(*magnitude_delta_y)+(*magnitude_delta_y);
          *x_max=*twice_magnitude_delta_x*(*num_columns);
          *y_max=*twice_magnitude_delta_y*(*num_rows);
          *delta_x=(*magnitude_delta_x);
          *(delta_y+24)=(*magnitude_delta_y);
          *(delta_x+48)=-(*magnitude_delta_x);
          *(delta_y+72)=-(*magnitude_delta_y);
          *delta_y=0;
          *(delta_x+24)=0;
          *(delta_y+48)=0;
          *(delta_x+72)=0;
          delta_index_2=-1;
          for (delta_index_1a=0; delta_index_1a < 4; delta_index_1a++)
            for (delta_index_1b=0; delta_index_1b < 4; delta_index_1b++)
              if (delta_index_1a != delta_index_1b)
                for (delta_index_1c=0; delta_index_1c < 4;
                 delta_index_1c++)
                  if ((delta_index_1a != delta_index_1c)
                  &&  (delta_index_1b != delta_index_1c))
                    for (delta_index_1d=0; delta_index_1d < 4;
                     delta_index_1d++)
                      if ((delta_index_1a != delta_index_1d)
                      &&  (delta_index_1b != delta_index_1d)
                      &&  (delta_index_1c != delta_index_1d))
                        {
                          delta_index_2=delta_index_2+1;
                          *(delta_x+(24*delta_index_1a+delta_index_2))
                           =*delta_x;
                          *(delta_y+(24*delta_index_1a+delta_index_2))
                           =*delta_y;
                          *(delta_x+(24*delta_index_1b+delta_index_2))
                           =*(delta_x+24);
                          *(delta_y+(24*delta_index_1b+delta_index_2))
                           =*(delta_y+24);
                          *(delta_x+(24*delta_index_1c+delta_index_2))
                           =*(delta_x+48);
                          *(delta_y+(24*delta_index_1c+delta_index_2))
                           =*(delta_y+48);
                          *(delta_x+(24*delta_index_1d+delta_index_2))
                           =*(delta_x+72);
                          *(delta_y+(24*delta_index_1d+delta_index_2))
                           =*(delta_y+72);
                        }
        }
      return;
    }

static void generate_maze(delta_x,delta_y,magnitude_delta_x,
 magnitude_delta_y,num_columns,num_rows,passage,path,r_n,
 twice_magnitude_delta_x,twice_magnitude_delta_y,wall,x_max,y_max,
 fatal_error)
  int *delta_x;
  int *delta_y;
  int *magnitude_delta_x;
  int *magnitude_delta_y;
  int *num_columns;
  int *num_rows;
  int *passage;
  int *path;
  int *r_n;
  int *twice_magnitude_delta_x;
  int *twice_magnitude_delta_y;
  int *wall;
  int *x_max;
  int *y_max;
  int *fatal_error;
    {
      int             finished;
      int             delta_index_1;
      int             delta_index_2;
      int             digit;
      int             digit_num;
      int             recurse;
      int             r_n_index_1;
      int             r_n_index_2;
      stack_2_rec_ptr stack_head;
      stack_2_rec_ptr stack_ptr;
      int             sum;
      int             tem_int;
      int             x;
      int             x_next;
      int             x_out;
      int             y;
      int             y_next;
      int             y_out;

      setcolor(*path);
      setfillstyle((unsigned int) SOLID_FILL,(unsigned int) *path);
      bar(0,0,*x_max,*y_max);
      if (*path != *wall)
        {
          setcolor((unsigned int) *wall);
          x_out=0;
          while (x_out <= *x_max)
            {
              line(x_out,0,x_out,*y_max);
              x_out+=(*twice_magnitude_delta_x);
            }
          y_out=0;
          while (y_out <= *y_max)
            {
              line(0,y_out,*x_max,y_out);
              y_out+=(*twice_magnitude_delta_y);
            }
        }
      sum=0;
      for (digit_num=1; digit_num <= 3; digit_num++)
        {
          digit=*r_n;
          r_n_index_1=0;
          for (r_n_index_2=1; r_n_index_2 < 8; r_n_index_2++)
            {
              tem_int=*(r_n+r_n_index_2);
              *(r_n+r_n_index_1)=tem_int;
              r_n_index_1++;
              digit+=tem_int;
              if (digit >= 29)
                digit-=29;
            }
          *(r_n+7)=digit;
          sum=29*sum+digit;
        }
      x=(2*(sum%(*num_columns))+1)*(*magnitude_delta_x);
      sum=0;
      for (digit_num=1; digit_num <= 3; digit_num++)
        {
          digit=*r_n;
          r_n_index_1=0;
          for (r_n_index_2=1; r_n_index_2 < 8; r_n_index_2++)
            {
              tem_int=*(r_n+r_n_index_2);
              *(r_n+r_n_index_1)=tem_int;
              r_n_index_1++;
              digit+=tem_int;
              if (digit >= 29)
                digit-=29;
            }
          *(r_n+7)=digit;
          sum=29*sum+digit;
        }
      y=(2*(sum%(*num_rows))+1)*(*magnitude_delta_y);
      setcolor((unsigned int) *passage);
      setfillstyle((unsigned int) SOLID_FILL,(unsigned int) *passage);
      finished=FALSE;
      recurse=TRUE;
      stack_head=NULL;
      while ((! finished) && (! *fatal_error))
        {
          if (recurse)
            {
              bar(x-(*magnitude_delta_x)+1,y-(*magnitude_delta_y)+1,
               x+(*magnitude_delta_x)-1,y+(*magnitude_delta_y)-1);
              delta_index_1=0;
              do
                {
                  delta_index_2=*r_n;
                  r_n_index_1=0;
                  for (r_n_index_2=1; r_n_index_2 < 8; r_n_index_2++)
                    {
                      tem_int=*(r_n+r_n_index_2);
                      *(r_n+r_n_index_1)=tem_int;
                      r_n_index_1++;
                      delta_index_2+=tem_int;
                      if (delta_index_2 >= 29)
                        delta_index_2-=29;
                    }
                  *(r_n+7)=delta_index_2;
                }
              while (delta_index_2 >= 24);
              recurse=FALSE;
            }
            while ((delta_index_1 < 4)
            &&     (! recurse)
            &&     (! *fatal_error))
              {
                x_next=x+2*(*(delta_x+(24*delta_index_1+delta_index_2)));
                if ((x_next <= 0) || (x_next >= *x_max))
                  delta_index_1++;
                else
                  {
                    y_next
                     =y+2*(*(delta_y+(24*delta_index_1+delta_index_2)));
                    if ((y_next <= 0) || (y_next >= *y_max))
                      delta_index_1++;
                    else
                      if (getpixel(x_next,y_next)
                       == (unsigned int)*path)
                        {
                          if (x == x_next)
                            {
                              y_out=(y+y_next)/2;
                              line(x-(*magnitude_delta_x)+1,y_out,
                               x+(*magnitude_delta_x)-1,y_out);
                            }
                          else
                            {
                              x_out=(x+x_next)/2;
                              line(x_out,y-(*magnitude_delta_y)+1,
                               x_out,y+(*magnitude_delta_y)-1);
                            }
                          x=x_next;
                          y=y_next;
                          if ((stack_ptr=(struct stack_2_rec *) malloc(
                           (unsigned) sizeof(struct stack_2_rec)))
                           == NULL)
                            {
                              *fatal_error=TRUE;
                              closegraph();
                              printf("? out of memory\n");
                            }
                          else
                            {
                              stack_ptr->next_ptr=stack_head;
                              stack_head=stack_ptr;
                              stack_head->index_1
                               =(unsigned char) delta_index_1;
                              stack_head->index_2
                               =(unsigned char) delta_index_2;
                              recurse=TRUE;
                            }
                        }
                      else
                        delta_index_1++;
                  }
              }
            if ((! recurse) && (! *fatal_error))
              {
                delta_index_1=(int) stack_head->index_1;
                delta_index_2=(int) stack_head->index_2;
                stack_ptr=stack_head;
                stack_head=stack_head->next_ptr;
                free((char *) stack_ptr);
                if (stack_head == NULL)
                  finished=TRUE;
                else
                  {
                    x-=
                     (2*(*(delta_x+(24*delta_index_1+delta_index_2))));
                    y-=
                     (2*(*(delta_y+(24*delta_index_1+delta_index_2))));
                  }
              }
        }
      if (! *fatal_error)
        {
          line(1,0,(*twice_magnitude_delta_x)-1,0);
          line(*x_max-(*twice_magnitude_delta_x)+1,*y_max,
           *x_max,*y_max);
          sound(1000);
          delay(333);
          nosound();
        }
      return;
    }

static void remove_rejected_attempts(delta_x,delta_y,erase,passage,
 stack_head,stack_ptr,x,x_next,y,y_next,fatal_error)
  int             *delta_x;
  int             *delta_y;
  int             *erase;
  int             *passage;
  stack_1_rec_ptr *stack_head;
  stack_1_rec_ptr *stack_ptr;
  int             *x;
  int             *x_next;
  int             *y;
  int             *y_next;
  int             *fatal_error;
    {
      int             delta_index_1;
      int             finished;
      int             recurse;
      stack_1_rec_ptr stack_start;

      stack_start=*stack_head;
      if (*erase != *passage)
        {
          recurse=TRUE;
          finished=FALSE;
          while ((! finished) && (! *fatal_error))
            {
              if (recurse)
                {
                  delta_index_1=0;
                  recurse=FALSE;
                }
              while ((delta_index_1 <= 3)
              &&     (! recurse))
                if (*stack_head == NULL)
                  {
                    *x_next=(*x)+(*(delta_x+(24*delta_index_1)));
                    *y_next=(*y)+(*(delta_y+(24*delta_index_1)));
                    if (getpixel(*x_next,*y_next)
                     == (unsigned int) *erase)
                      {
                        *x_next+=(*(delta_x+(24*delta_index_1)));
                        *y_next+=(*(delta_y+(24*delta_index_1)));
                        *x=(*x_next);
                        *y=(*y_next);
                        if ((*stack_ptr=(struct stack_1_rec *) malloc(
                         (unsigned) sizeof(struct stack_1_rec)))
                         == NULL)
                          {
                            *fatal_error=TRUE;
                            closegraph();
                            printf("? out of memory\n");
                          }
                        else
                          {
                            (*stack_ptr)->next_ptr=*stack_head;
                            *stack_head=(*stack_ptr);
                            (*stack_head)->index_1
                             =(unsigned char) delta_index_1;
                            recurse=TRUE;
                          }
                      }
                    else
                      delta_index_1++;
                  }
                else
                  if ((delta_index_1 + 2) % 4
                   == (int) (*stack_head)->index_1)
                    delta_index_1++;
                  else
                    {
                      *x_next=(*x)+(*(delta_x+(24*delta_index_1)));
                      *y_next=(*y)+(*(delta_y+(24*delta_index_1)));
                      if (getpixel(*x_next,*y_next)
                       == (unsigned int) *erase)
                        {
                          *x_next+=(*(delta_x+(24*delta_index_1)));
                          *y_next+=(*(delta_y+(24*delta_index_1)));
                          *x=(*x_next);
                          *y=(*y_next);
                          if ((*stack_ptr=(struct stack_1_rec *) malloc(
                           (unsigned) sizeof(struct stack_1_rec)))
                           == NULL)
                            {
                              *fatal_error=TRUE;
                              closegraph();
                              printf("? out of memory\n");
                            }
                          else
                            {
                              (*stack_ptr)->next_ptr=(*stack_head);
                              *stack_head=(*stack_ptr);
                              (*stack_head)->index_1
                               =(unsigned char) delta_index_1;
                              recurse=TRUE;
                            }
                        }
                      else
                        delta_index_1++;
                    }
              if ((delta_index_1 > 3) && (! *fatal_error))
                {
                  if (stack_start == *stack_head)
                    finished=TRUE;
                  else
                    {
                      setcolor((unsigned int) *passage);
                      *x_next=(*x);
                      *y_next=(*y);
                      delta_index_1=(int) ((*stack_head)->index_1);
                      *stack_ptr=(*stack_head);
                      (*stack_head)=(*stack_head)->next_ptr;
                      free((char *) *stack_ptr);
                      *x-=(2*(*(delta_x+(24*delta_index_1))));
                      *y-=(2*(*(delta_y+(24*delta_index_1))));
                      line(*x,*y,*x_next,*y_next);
                      delta_index_1++;
                    }
                }
            }
        }
      return;
    }

static void let_user_try_to_solve(delta_x,delta_y,erase,key_pressed,
 magnitude_delta_x,magnitude_delta_y,passage,path,wall,y_max,
 fatal_error)
  int *delta_x;
  int *delta_y;
  int *erase;
  int *key_pressed;
  int *magnitude_delta_x;
  int *magnitude_delta_y;
  int *passage;
  int *path;
  int *wall;
  int *y_max;
  int *fatal_error;
    {
      int             color;
      int             delta_index_1;
      int             frequency;
      int             passage_found;
      stack_1_rec_ptr stack_head;
      stack_1_rec_ptr stack_ptr;
      int             x;
      int             x_next;
      int             y;
      int             y_next;

      stack_head=NULL;
      x=*magnitude_delta_x;
      y=*magnitude_delta_y;
      y_next=0;
      setcolor((unsigned int) *path);
      line(x,0,x,y);
      do
        {
          do
            {
              passage_found=TRUE;
              *key_pressed=getch();
              if ((*key_pressed != (int) 'Q')
              &&  (*key_pressed != (int) 'q')
              &&  (*key_pressed != (int) 'S')
              &&  (*key_pressed != (int) 's'))
                {
                  if (*key_pressed == 0)
                    {
                      *key_pressed=getch();
                      switch (*key_pressed)
                        {
                          case 72:
                             delta_index_1=3;
                             break;
                          case 77:
                             delta_index_1=0;
                             break;
                          case 80:
                             delta_index_1=1;
                             break;
                          case 75:
                             delta_index_1=2;
                             break;
                          default:
                            {
                              passage_found=FALSE;
                              sound(120);
                              delay(278);
                              nosound();
                              *key_pressed=(int) ' ';
                              break;
                            }
                        }
                    }
                  else
                    {
                      switch (*key_pressed)
                        {
                          case 56:
                            delta_index_1=3;
                            break;
                          case 54:
                            delta_index_1=0;
                            break;
                          case 50:
                            delta_index_1=1;
                            break;
                          case 52:
                            delta_index_1=2;
                            break;
                          default:
                            {
                              passage_found=FALSE;
                              sound(120);
                              delay(278);
                              nosound();
                              break;
                            }
                        }
                    }
                  if (passage_found)
                    {
                      x_next=x+(*(delta_x+(24*delta_index_1)));
                      y_next=y+(*(delta_y+(24*delta_index_1)));
                      color=(int) getpixel(x_next,y_next);
                      if (color == *wall)
                        if (color == *path)
                          if (stack_head == NULL)
                            {
                              passage_found=FALSE;
                              sound(120);
                              delay(278);
                              nosound();
                            }
                          else
                            {
                              if
                               ((((int) (stack_head->index_1)) + 2) % 4
                               != delta_index_1)
                                {
                                  passage_found=FALSE;
                                  sound(120);
                                  delay(278);
                                  nosound();
                                }
                            }
                        else
                          {
                            passage_found=FALSE;
                            sound(120);
                            delay(278);
                            nosound();
                          }
                      else
                        {
                          if (y_next == 0)
                            {
                              passage_found=FALSE;
                              sound(120);
                              delay(278);
                              nosound();
                            }
                        }
                    }
                }
            }
          while ((! passage_found)
          &&     (*key_pressed != (int) 'Q')
          &&     (*key_pressed != (int) 'q')
          &&     (*key_pressed != (int) 'S')
          &&     (*key_pressed != (int) 's'));
          if ((*key_pressed != (int) 'Q')
          &&  (*key_pressed != (int) 'q')
          &&  (*key_pressed != (int) 'S')
          &&  (*key_pressed != (int) 's'))
            {
              if (stack_head == NULL)
                {
                  if ((stack_ptr=(struct stack_1_rec *) malloc(
                   (unsigned) sizeof(struct stack_1_rec))) == NULL)
                    {
                      *fatal_error=TRUE;
                      closegraph();
                      printf("? out of memory\n");
                    }
                  else
                    {
                      stack_ptr->next_ptr=stack_head;
                      stack_head=stack_ptr;
                      stack_head->index_1=(unsigned char) delta_index_1;
                    }
                }
              else
                if ((((int) (stack_head->index_1)) +2) % 4
                 == delta_index_1)
                  {
                    stack_ptr=stack_head;
                    stack_head=stack_head->next_ptr;
                    free((char *) stack_ptr);
                  }
                else
                  {
                    if ((stack_ptr=(struct stack_1_rec *) malloc(
                     (unsigned) sizeof(struct stack_1_rec))) == NULL)
                      {
                        *fatal_error=TRUE;
                        closegraph();
                        printf("? out of memory\n");
                      }
                    else
                      {
                        stack_ptr->next_ptr=stack_head;
                        stack_head=stack_ptr;
                        stack_head->index_1
                         =(unsigned char) delta_index_1;
                      }
                  }
              if (! *fatal_error)
                {
                  x_next+=(*(delta_x+(24*delta_index_1)));
                  y_next+=(*(delta_y+(24*delta_index_1)));
                  if (y_next <= *y_max)
                    {
                      if (color == *path)
                        setcolor((unsigned int) *erase);
                      else
                        setcolor((unsigned int) *path);
                      line(x,y,x_next,y_next);
                    }
                  else
                    {
                      setcolor((unsigned int) *path);
                      line(x,y,x_next,*y_max);
                    }
                  x=x_next;
                  y=y_next;
                }
            }
        }
      while ((y_next <= *y_max)
      &&     (*key_pressed != (int) 'Q')
      &&     (*key_pressed != (int) 'q')
      &&     (*key_pressed != (int) 'S')
      &&     (*key_pressed != (int) 's')
      &&     (! *fatal_error));
      if (! *fatal_error)
        {
          if (y_next > *y_max)
            {
              frequency=10;
              for (delta_index_1=1; delta_index_1 <= 100;
               delta_index_1++)
                {
                  sound(frequency);
                  delay(56);
                  nosound();
                  frequency+=10;
                };
              do
                {
                  *key_pressed=getch();
                  if ((*key_pressed != (int) 'Q')
                  &&  (*key_pressed != (int) 'q')
                  &&  (*key_pressed != (int) 'S')
                  &&  (*key_pressed != (int) 's'))
                    {
                      sound(120);
                      delay(278);
                      nosound();
                    }
                  if (*key_pressed == 0)
                    {
                      *key_pressed=getch();
                      *key_pressed=(int) ' ';
                    }
                }
              while ((*key_pressed != (int) 'Q')
              &&     (*key_pressed != (int) 'q')
              &&     (*key_pressed != (int) 'S')
              &&     (*key_pressed != (int) 's'));
            }
          if ((*key_pressed == (int) 'S')
          ||  (*key_pressed == (int) 's'))
            {
              while ((stack_head != NULL) && (! *fatal_error))
                {
                  remove_rejected_attempts(delta_x,delta_y,erase,
                   passage,&stack_head,&stack_ptr,&x,&x_next,&y,
                   &y_next,fatal_error);
                  if (! *fatal_error)
                    {
                      delta_index_1=(int) (stack_head->index_1);
                      x_next=x-2*(*(delta_x+(24*delta_index_1)));
                      y_next=y-2*(*(delta_y+(24*delta_index_1)));
                      setcolor((unsigned int) *passage);
                      if (y <= *y_max)
                        line(x,y,x_next,y_next);
                      else
                        line(x,*y_max,x_next,y_next);
                      x=x_next;
                      y=y_next;
                      stack_ptr=stack_head;
                      stack_head=stack_head->next_ptr;
                      free((char *) stack_ptr);
                    }
                }
              if (! *fatal_error)
                remove_rejected_attempts(delta_x,delta_y,erase,passage,
                 &stack_head,&stack_ptr,&x,&x_next,&y,&y_next,
                 fatal_error);
            }
          else
            while (stack_head != NULL)
              {
                stack_ptr=stack_head;
                stack_head=stack_head->next_ptr;
                free((char *) stack_ptr);
              }
        }
      return;
    }

static void optionally_have_computer_solve(delta_x,delta_y,key_pressed,
 magnitude_delta_x,magnitude_delta_y,passage,path,y_max,fatal_error)
  int *delta_x;
  int *delta_y;
  int *key_pressed;
  int *magnitude_delta_x;
  int *magnitude_delta_y;
  int *passage;
  int *path;
  int *y_max;
  int *fatal_error;
    {
      int             finished;
      unsigned char   delta_index_1;
      int             recurse;
      stack_1_rec_ptr stack_head;
      stack_1_rec_ptr stack_ptr;
      int             x;
      int             x_next;
      int             y;
      int             y_next;

      if ((*key_pressed == 'S')
      ||  (*key_pressed == 's'))
        {
          x=*magnitude_delta_x;
          y=*magnitude_delta_y;
          y_next=y+(*magnitude_delta_y);
          setcolor((unsigned int) *path);
          line(x,0,x,y);
          finished=FALSE;
          recurse=TRUE;
          stack_head=NULL;
          while ((! finished) && (! *fatal_error))
            {
              if (recurse)
                {
                  delta_index_1=0;
                  recurse=FALSE;
                };
              while ((delta_index_1 < 4)
              &&     (! finished)
              &&     (! recurse)
              &&     (! *fatal_error))
                {
                  x_next=x+(*(delta_x+(24*delta_index_1)));
                  y_next=y+(*(delta_y+(24*delta_index_1)));
                  if (getpixel(x_next,y_next)
                   == (unsigned int) *passage)
                    {
                      x_next+=(*(delta_x+(24*delta_index_1)));
                      y_next+=(*(delta_y+(24*delta_index_1)));
                      if (y_next <= *y_max)
                        {
                          setcolor((unsigned int) *path);
                          line(x,y,x_next,y_next);
                          x=x_next;
                          y=y_next;
                          if ((stack_ptr=(struct stack_1_rec *) malloc(
                           (unsigned) sizeof(struct stack_1_rec)))
                           == NULL)
                            {
                              *fatal_error=TRUE;
                              closegraph();
                              printf("? out of memory\n");
                            }
                          else
                            {
                              stack_ptr->next_ptr=stack_head;
                              stack_head=stack_ptr;
                              stack_head->index_1
                               =(unsigned char) delta_index_1;
                              recurse=TRUE;
                            }
                        }
                      else
                        finished=TRUE;
                    }
                  else
                    delta_index_1++;
                };
              if ((delta_index_1 >= 4) && (! *fatal_error))
                {
                  setcolor((unsigned int) *passage);
                  x_next=x;
                  y_next=y;
                  delta_index_1=stack_head->index_1;
                  stack_ptr=stack_head;
                  stack_head=stack_head->next_ptr;
                  free((char *) stack_ptr);
                  x-=(2*(*(delta_x+(24*delta_index_1))));
                  y-=(2*(*(delta_y+(24*delta_index_1))));
                  line(x,y,x_next,y_next);
                  delta_index_1++;
                }
            };
          if (! *fatal_error)
            {
              line(x,y,x,*y_max);
              sound(1000);
              delay(333);
              nosound();
              *key_pressed=getch();
              if (*key_pressed == 0)
                *key_pressed=getch();
            }
        }
      return;
    }
