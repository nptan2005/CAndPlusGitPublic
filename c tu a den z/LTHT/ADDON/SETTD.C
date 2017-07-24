typedef int FILE;
#define CMOS_ADR 0x70
#define CMOS_DATA 0x71
#define CMOS_BYTES 64
extern char *index();
extern int _rax, _rbx, _rcx, _rdx;
int RAX, RBX, RCX, RDX;
char *p; char cmosfilename[] = "\\CMOSINFO";
char cmos[CMOS_BYTES]; 
int hour,minute,second; 
int day,month,year,century; 
int dayofweek; 
char *monthname[] = {"Jan", 
                    "Feb",
                    "Mar",
                    "Apr",
                    "May",
                    "Jun",
                    "Jul",
                    "Aug",
                    "Sep",
                    "Oct",
                    "Nov",
                    "Dec"
                   };
char *dayname[] = {"Sunday",
                  "Monday",
                  "Tuesday",
                  "Wednesday",
                  "Thursday",
                  "Friday",
                  "Saturday"
                 };

main(argc,argv)
int argc;
char *argv[];
{int i,j,flag;
 FILE *fp;
 if (argc < 2)
   {printf("\n");
    printf("\nThis program will save and restore the AT's CMOS data, which");
    printf("\nincludes, but is not limited to, the configuration, and the");
    printf("\ntime and date.  This program will also let you change the time");
    printf("\nand date (The DOS DATE and TIME commands do not work).");
    printf("\n");
    printf("\nTo save the configuration (do this before your battery dies)");
    printf("\nC:>settd /s (will store configuration in file \\CMOSINFO.)");
    printf("\n");
    printf("\nTo restore the configuration (do this after you replace your battery)");
    printf("\nC:>settd /r (will restore from file \\CMOSINFO.)");
    printf("\n");
    printf("\nTo set the time and date (either one is optional):");
    printf("\nC:>settd hh:mm:ss dd-mm-yy");
    printf("\n");
    printf("\nTo display the current time and date:");
    printf("\nC:>settd /d");
    printf("\n");
    exit(0);
   }
 for (i=1; i<argc; ++i)
   {p = index(argv[i],'/');
    if (p != 0)
      {flag = toupper(*(p+1));
       switch(flag)
         {case 'S': /* Save CMOS info */
                    for (j = 0; j<CMOS_BYTES; ++j)
                       {_outb(j,CMOS_ADR);         /* Tell CMOS which byte */
                        j = j;                     /* Kill some time */
                        cmos[j] = _inb(CMOS_DATA); /* Read byte from CMOS */
                       }
                    fp = creat(cmosfilename);
                    write(fp,cmos,CMOS_BYTES);
                    close(fp);
                    break;

          case 'R': /* Restore CMOS info */
                    get_current_td();
                    fp = open(cmosfilename,0);
                    read(fp,cmos,CMOS_BYTES);
                    close(fp);
                    for (j = 0; j<CMOS_BYTES; ++j)
                       {_outb(j,CMOS_ADR);         /* Tell CMOS which byte */
                        j = j;                     /* Kill some time */
                        _outb(cmos[j],CMOS_DATA);  /* Send byte to CMOS */
                       }
                    set_current_td();
                    break;

          case 'D': /* Display current time and date */
                    get_current_td();
                    printf("\n\n%02d:%02d:%02d  %s  %d %s %d\n\n"
                          ,hour
                          ,minute
                          ,second
                          ,dayname[dayofweek]
                          ,day
                          ,monthname[month-1]
                          ,century * 100 + year
                          );
                    break;
         }
      }
    if (index(argv[i],':') != 0) /* Set time */
      {sscanf(argv[i],"%d:%d:%d",&hour,&minute,&second);
       set_current_t();
      }
    if (index(argv[i],'-') != 0) /* Set date */
      {sscanf(argv[i],"%d-%d-%d",&day,&month,&year);
       if (month > 12) {j = month; month = day; day = j;}
       if (year < 100) year += 1900;
       if (year < 1980) year += 100;
       century = year / 100;
       year %= 100;
       set_current_d();
      }
   }
} 

get_current_td()
{
 RAX = 0x2A00;
 _rax = RAX;
 _doint(0x21);
 RAX = _rax;
 RCX = _rcx;
 RDX = _rdx;
 dayofweek = RAX & 0x00FF;
 century = RCX / 100;
 year = RCX % 100;
 month = (RDX >> 8) & 0x00FF;
 day = RDX & 0x00FF;
 RAX = 0x2C00;
 _rax = RAX;
 _doint(0x21);
 RAX = _rax; RCX = _rcx; RDX = _rdx;
 hour = (RCX >> 8) & 0x00FF;
 minute = RCX & 0x00FF;
 second = (RDX >> 8) & 0x00FF;
}

set_current_td()
{set_current_t();
 set_current_t();
}

set_current_t()
{
 RCX = (((hour/10) << 4) + (hour % 10)) << 8;
 RCX += ((minute/10) << 4) + (minute % 10);
 RDX = (((second/10) << 4) + (second % 10)) << 8;
 RAX = 0x0300;
 _rax = RAX; _rcx = RCX; _rdx = RDX;
 _doint(0x1A);
 RCX = (hour << 8) + minute;
 RDX = second << 8;
 RAX = 0x2D00;
 _rax = RAX; _rcx = RCX; _rdx = RDX;
 _doint(0x21);
}

set_current_d()
{
 RCX = (((century/10) << 4) + (century % 10)) << 8;
 RCX += ((year/10) << 4) + (year % 10);
 RDX = (((month/10) << 4) + (month % 10)) << 8;
 RDX += ((day/10) << 4) + (day % 10);
 RAX = 0x0500;
 _rax = RAX; _rcx = RCX; _rdx = RDX;
 _doint(0x1A);
 RCX = century * 100 + year;
 RDX = (month << 8) + day;
 RAX = 0x2B00;
 _rax = RAX; _rcx = RCX; _rdx = RDX;
 _doint(0x21);
}
