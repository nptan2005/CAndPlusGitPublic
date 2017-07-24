/*Phuong phap ROMBERG tinh tich phan cua ham
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
	int i ,j , m , n , mu , max , i3 , j1;
	double a , b , h ,epslon , tc;
	double s0 , s1 , s2 , i1 , i2;
	float c[100][100] ;
	enum BOOLEAN t , t1;

	clrscr();
	printf("TICH PHAN BANG PHUONG PHAP ROMBERG    y = exp(-x*x)\n");
	printf("CAN DUOI a=");
	fflush(stdin);
	scanf("%lf",&a);
	printf("CAN TREN b=");
	fflush(stdin);
	scanf("%lf",&b);
	printf("SAI SO epslon=");
	fflush(stdin);
	scanf("%lf",&epslon);
	printf("SO BUOC LAP max=");
	fflush(stdin);
	scanf("%d",&max);
	s1 = 0;
	s2 = 0;
	n = 1 ;
	h = b - a ;
	s0 = f(a) + f(b) ;
	i2 = h*s0/2.0 ;
	c[0][0] = i2 ;
	printf("TICH PHAN BROMBERG\n");
	printf("CHO HAM   y = exp(-x*x)\n");
	printf("TREN DOAN [a,b]=[%lf,%lf]\n" , a , b);
	printf("DO LECH epslon = %12.11lf\n" , epslon);
	t = false ;
	i = 1 ;
	do
	{
		i1 = i2 ;
		s1 += s2 ;
		m = 2*n ;
		h /=2 ;
		s2 = 0 ;
		for (i3 = 1 ; i3 <= n ; i3++) 	s2 +=f( a + (2*i3 -1)*h ) ;
		n = m ;
		i2 = h*(s0 + 2*s1 + 2*s2)/2.0 ;
		c[i][0] = i2 ;
		j = 1 ;
		mu = 1 ;
		t1 = false ;
		do
		{
			mu *= 4 ;
			tc = ( mu*c[i][j - 1] - c[i - 1][j - 1] )/(mu - 1) ;
			c[i][j] = tc ;
			if ( fabs(c[i][j] - c[i - 1][j]) < epslon )
			{
				t1 = true ;
				t = true ;
				printf("\tTICH PHAN    I = %lf\n" , c[i][j]);
				printf("\tMA TRAN TICH PHAN ROMBERG\n");
				for (i3 = 0 ; i3 <= i ; i3++)
				{
					for (j1 = 0 ; j1 <= i - 1 ; j1++)
						printf("  %lf" , c[i3][j1]);
					printf("\n") ;
				}
				printf("\tTICH PHAN    I = %12.3lf\n" ,c[i][j]);
//				getch();
			}
			j++ ;
			if ( j > i ) t1 = true ;
		} while (!t1) ;
		i++ ;
		if ( i > max )
		{
			t = true ;
			printf("LAP KHONG HOI TU SAU %d BUOC\n" , max );
		}
	} while (!t) ;
	getch();
}

