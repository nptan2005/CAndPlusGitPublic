/*Phuong phap hinh thang tinh tich phan cua ham
	f(x) = exp(-x*x) doan [a,b]      */
#include <stdio.h>
#include <conio.h>
#include <math.h>

enum BOOLEAN { false = 0 , true };
double f(float x)
{
	double tri ;
	double y;

	y = -x*x ;
	tri = exp(y) ;
	return tri ;
}
void main()
{
	int i , m , n ;
	double a , b , h ,epslon ;
	double s0 , s1 , s2 , i1 , i2;
	enum BOOLEAN t ;

	clrscr();
	printf("TICH PHAN BANG PHUONG PHAP HINH THANG    y = exp(-x*x)\n");
	printf("CAN DUOI a=");
	fflush(stdin);
	scanf("%lf",&a);
	printf("CAN TREN b=");
	fflush(stdin);
	scanf("%lf",&b);
	printf("SAI SO epslon=");
	fflush(stdin);
	scanf("%lf",&epslon);
	s1 = 0;
	s2 = 0;
	n = 1 ;
	h = b - a ;
	s0 = f(a) + f(b) ;
	i2 = h*s0/2.0 ;
	printf("TICH PHAN BANG PHUONG PHAP HINH THANG\n");
	printf("CHO HAM   y = exp(-x*x)\n");
	printf("TREN DOAN [a,b]=[%lf,%lf]\n" , a , b);
	printf("DO LECH epslon = %12.11lf\n" , epslon);
	t = false ;
	do
	{
		i1 = i2 ;
		s1 +=s2 ;
		m = 2*n ;
		h /=2 ;
		s2 = 0 ;
		for (i = 1 ; i <= n ;i++) 	s2 +=f( a + (2*i -1)*h ) ;
		n = m ;
		i2 = h*(s0 + 2*s1 + 2*s2)/2.0 ;
		if ( fabs(i2 - i1) < epslon )
		{
			t = true ;
			printf("\tTICH PHAN    I = %12.3lf\n" ,i2);
		}
	} while (!t) ;
	getch();
}

