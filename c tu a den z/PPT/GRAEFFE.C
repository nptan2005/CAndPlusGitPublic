/*Phuong phap  GRAEFFE tim cac nghiem cua da thuc bac n*/
#include <stdio.h>
#include <conio.h>
#include <math.h>

enum BOOLEAN { false = 0 , true };

void main()
{
	double c , d , s ,c1 , d1 , d2;
	int i , j , k , ik , n , sbl ; // sbl so buoc lap
	int max ; //  so buoc lap toi da
	double a[51] , b[50] ;
	enum BOOLEAN t ;

	clrscr();
	printf("TIM NGHIEM DA THUC VOI n NGHIEM THUC PHAN BIEC \n");
	printf("BAC CUA DA THUC :");
	fflush(stdin);
	scanf("%d",&n);
	printf("SO BUOC LAP TOI DA max(<=6)=");
	fflush(stdin);
	scanf("%d",&max);
	a[0] = 1 ;
	printf("DOC CAC HE SO CUA DA THUC\n");
	for (i = 1 ; i <= n ; i++)		scanf("%lf",&a[i]);
	printf("CAC SO LIEU BAN DAU\n");
	printf("\n");
	printf("BAC CUA DA THUC n =%d\n",n);
	printf("SO BUOC LAP TOI DA max =%d\n" , max);
	printf("CAC HE SO CUA DA THUC\n");
	for (i = 0 ; i <= n ; i++)		printf("  %lf",a[i]);
	printf("\n");
	c1 = fabs(a[n]) ;
	d1 = 1.0/(1.0*n) ;
	c1 = d1*log(c1) ;
	c = exp(c) ;
	d = c ;
	d2 = 1 ;
	for (i = 1 ; i <= n ; i++)
	{
		d2 *= d ;
		a[i] /= d2 ;
	}
	sbl = 1 ;
	printf("\n");
	printf("CAC KET QUA TRUNG GIAN\n");
	printf("\n");
	printf("m      a0           a1       a2     a3\n");
	printf("\n");
	printf("%d" , sbl);
	for (i = 0 ; i <= n ; i++)			printf("  %lf",a[i]);
	for (ik = 1 ; ik <= max ; ik++)
	{
		sbl *= 2 ;
		for (i = 1 ; i <= n ; i++)
		{
			d = 1 ;
			k = i ;
			j = i ;
			b[i - 1] = a[i]*a[i] ;
			t = true ;
			while ( t )
			{
				k-- ;
				j++ ;
				d = -d ;
				b[i -1] += 2*d*a[k]*a[j] ;
				if ( (k <= 0) || (j >= n) )	t = false ;
			}
		}
		for (i = 1 ; i <= n ; i++)	a[i] = b[i - 1] ;
		printf("\n");
		printf("%d" , sbl);
		for (i = 0 ; i <= n ; i++)	printf("  %lf" , a[i] );
	}
	d = 1.0/(1.0*sbl) ;
	s = d*log(a[1]) ;
	s = exp(s) ;
	b[0] = c*s ;
	for (i = 2 ; i <= n ; i++)
	{
		s = a[i]*a[i - 1] ;
		s = d*log(s) ;
		s = exp(s) ;
		b[i - 1] = c*s ;
	}
	printf("\n");
	printf("NGHIEM CUA DA THUC\n " );
	for (i = 0 ; i < n ; i++) printf("   x[%d] =%lf" , i , b[i]) ;
	printf("\n");
	getch() ;
}
