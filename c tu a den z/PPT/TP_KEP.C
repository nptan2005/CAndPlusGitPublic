/*Phuong phap hinh thang tinh tich phan kep cua ham
	f(x) = exp(2x + y) doan [a,b]      */
#include <stdio.h>
#include <conio.h>
#include <math.h>

enum BOOLEAN { false = 0 , true };
double f(float x , float y)
{
	double tri ;
	double t;

	t = 2*x + y ;
	tri = exp(t) ;
	return tri ;
}
void main()
{
	int i , j , m , n ;
	double a , b , c , d , hx , hy , epslon ;
	double s0 , s1 , s2 , i1 , i2;
	enum BOOLEAN t ;

	clrscr();
	printf("TICH PHAN KEP BANG PHUONG PHAP HINH THANG    y = exp(2x + y)\n");
	printf("CAN DUOI a=");
	fflush(stdin);
	scanf("%lf",&a);
	printf("CAN TREN b=");
	fflush(stdin);
	scanf("%lf",&b);
	printf("CAN DUOI c=");
	fflush(stdin);
	scanf("%lf",&c);
	printf("CAN TREN d=");
	fflush(stdin);
	scanf("%lf",&d);
	printf("SAI SO epslon=");
	fflush(stdin);
	scanf("%lf",&epslon);
	n = 1 ;
	hx = b - a ;
	hy = d - c ;
	s1 = f(a,c) + f(a,d) + f(b,c) + f(b,d)  ;
	i1 = s1/4.0 ;
	printf("TICH PHAN KEP BANG PHUONG PHAP HINH THANG\n");
	printf("CHO HAM   y = exp(2x + y)\n");
	printf("TREN DOAN [a,b]=[%lf,%lf]\n" , a , b);
	printf("TREN DOAN [c,d]=[%lf,%lf]\n" , c , d);
	printf("DO LECH epslon = %12.11lf\n" , epslon);
	t = false ;
	do
	{
		n *= 2 ;
		hx /= 2 ;
		hy /= 2 ;
		s2 = 0 ;
		for (i = 0 ; i <= n ;i++)
			for (j = 0 ; j <= n ;j++)
			{
				if ( (i == 0) || ( i == n ) || (j == 0) || (j == n) )
					s2 += 2*f( a + i*hx , c + j*hy ) ;
				if ( (i > 0) && ( i < n ) && (j > 0) && (j < n) )
					s2 += 4*f( a + i*hx , c + j*hy ) ;
			}
		s2 -= s1 ;
		i2 = hx*hy*s2/4.0 ;
		printf("\tn =%d    I = %12.3lf\n" , n ,i2);
		if ( fabs(i2 - i1) < epslon )
		{
			t = true ;
			printf("\tTICH PHAN    I = %12.3lf\n" ,i2);
		}
		i1 = i2 ;
	} while (!t) ;
	getch();
}

