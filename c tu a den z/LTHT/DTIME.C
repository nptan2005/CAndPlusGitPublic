/* Hien ngay va gio hien tai */
#include <time.h>
#include <stddef.h>
static char *Vdays[] = {"Thu Hai", "Thu Ba", "Thu Tu", "Thu Nam",
                       "Thu Sau", "Thu Bay", "Chu Nhat"};
static char *days[]= {"Monday", "Tuesday", "Wednesday", "Thursday", 
                      "Friday", "Saturday", "Sunday"};
static char *Vmont[] = {"Gieng", "Hai", "Ba", "Tu",
                       "Nam", "Sau", "Bay", "Tam",
                       "Chin", "Muoi", "Muoi Mot", "Muoi Hai"};
static char *mont[]= {"January", "February", "March", "April", 
                      "May", "June", "July", "August", 
                      "September", "October", "November", "December"};
void main()
{
  register int i;
  char bufr[40];
  char cmon[10],cday[10],ctime[10];
  int  nday,nyear;
  struct tm *ptr;
  time_t lt;

	lt=time(NULL);
	ptr=localtime(&lt);
	strcpy(bufr,asctime(ptr));
	sscanf(bufr,"%s %s %d %s %d",cday,cmon,&nday,ctime,&nyear);

	ctime[strlen(ctime)-3]='\0';
	for(i=0; i<7; i++)
	  if(strncmp(days[i],cday,3)==0)
	     break;
	strcpy(cday,Vdays[i]);
	for(i=0; i<12; i++)
	  if(strncmp(mont[i],cmon,3)==0)
	     break;
	strcpy(cmon, Vmont[i]);
  printf("\n%s, Ngay %d Thang %s Nam %d \tGio : %s\n",cday, nday,cmon,nyear,ctime);
}
