/*Phuong phap NEWTON(phuong phap tiep tuyen) tim nghiem gan dung cua
phuong trinh	sin(x - x*xcos(x) = 0 tren  doan [a,b]      */
#include <stdio.h>
#include <conio.h>
#include <math.h>

enum BOOLEAN { false = 0 , true };
float f(float x)
{
	float tri ;

	tri = sin(x) ;
	return tri ;
}
float f1(float x)
{
	float tri ;

	tri = cos(x) ;
	return tri ;
}


void main()
{
	float a , b , epslon , fa , fb , y , x , x1 , fc;
	int sbl ; // so buoc lap
	int max ; //  so buoc lap toi da
	enum BOOLEAN t ;

	clrscr();
	printf("PHUONG PHAP TIEP TUYEN TIM NGHIEM GAN DUNG\n");
	printf("GIAI PHUONG TRINH : sin(x) = 0\n");
	printf("NHAP CAC SO LIEU BAN DAU \n");
	printf("CAN DUOI a=");
	fflush(stdin);
	scanf("%f",&a);
	printf("CAN TREN b=");
	fflush(stdin);
	scanf("%f",&b);
	printf("SAI SO epslon=");
	fflush(stdin);
	scanf("%f",&epslon);
	printf("SO BUOC LAP TOI DA max=");
	fflush(stdin);
	scanf("%d",&max);
	fa = f(a) ;
	fb = f(b) ;
	if (fa*fb > 0)  printf("f(a) va f(b) cung dau\n");
	if (fa == 0) printf("NGHIEM PHUONG TRINH x = %f\n " , a);
	if (fb == 0) printf("NGHIEM PHUONG TRINH x = %f\n " , b);
	if (fa*fb < 0)
	{
		if ( fabs(fa) <= fabs(fb ) )
		{
			y = fa ;
			x = a ;
		}
		if ( fabs(fa) > fabs(fb ) )
		{
			y = fb ;
			x = b ;
		}
		sbl = 1 ;
		t = false ;
		printf("PHUONG PHAP TIEP TUYEN TIM NGHIEM CUA PHUONG TRINH\n");
		printf("\tsin(x) [%f ,%f]\n" , a , b);
		printf("SAI SO epslon = %f\n" , epslon);
		printf("CAC KET QUA TRUNG GIAN\n");
		do
		{
			fc = f1(x) ;
			printf("BUOC LAP THU %d    x = %f\n" , sbl , x);
			if (fabs(fc) < 0.000001)
			{
				printf("DAO HAM CUA HAM f(x) < 0.000001\n " );
				t = true ;
			}
			if (fabs(fc) >= 0.000001)
			{
				x1 = x - sin(x)/fc ;
				if (fabs(x1 - x) < epslon)
				{
					t = true ;
					printf("NGHIEM PHUONG TRINH x = %f\n " , x1);
				}
				x = x1 ;
			}
			sbl++ ;
			if (sbl > max)
			{
				t = true ;
				printf("SAU %d BUOC LAP CHUA HOI TU\n " , max);
				printf("\n " );
			}
		} while (!t) ;
	}
	getch();
}

