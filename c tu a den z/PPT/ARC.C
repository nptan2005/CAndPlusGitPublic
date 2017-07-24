/*Phuong phap REGULA-FALSI(phuong phap day cung) tim nghiem gan dung cua
phuong trinh	sin(x - x*xcos(x) = 0 tren  doan [a,b]      */
#include <stdio.h>
#include <conio.h>
#include <math.h>

enum BOOLEAN { false = 0 , true };
float f(float x)
{
	float tri ;

	tri = sin(x) - cos(x)*x*x ;
	return tri ;
}

void main()
{
	float a , b , c , epslon , fa , fb , fc;
	int sbl ; // so buoc lap
	int max ; //  so buoc lap toi da
	enum BOOLEAN t ;

	clrscr();
	printf("PHUONG PHAP DAY CUNG TIM NGHIEM GAN DUNG\n");
	printf("GIAI PHUONG TRINH : sin(x) - x*x*cos(x)\n");
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
		sbl = 0 ;
		t = false ;
		printf("PHUONG PHAP DAY CUNG TIM NGHIEM CUA PHUONG TRINH\n");
		printf("\tsin(x) - x*x*cos(x) =0  	[%f ,%f]\n" , a , b);
		printf("SAI SO epslon = %f\n" , epslon);
		printf("CAC KET QUA TRUNG GIAN\n");
		do
		{
			sbl++ ;
			c = (a*fb + b*fa)/(fb - fa) ;
			printf("BUOC THU %d c = %f\n" , sbl , c);
			fc = f(c) ;
			if (fc == 0)
			{
				printf("NGHIEM PHUONG TRINH x = %f\n " , c);
				t = true ;
			}
			if (fc*fa < 0)
			{
				b = c ;
				fb = fc ;
			}

			if (fc*fb < 0)
			{
				a = c ;
				fa = fc ;
			}
			if (fabs(b - a) < epslon)
			{
				t = true ;
				printf("NGHIEM PHUONG TRINH x = %f\n " , c);
				printf("\n " );
			}
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
