/*Phuong phap POWER tim tri rieng lon nhat & nho nhat*/
#include <stdio.h>
#include <conio.h>
#include <math.h>

enum BOOLEAN { false = 0 , true };

void main()
{
	int i , j , k , n , max ;
	float  s , epslon , t0 , t1;
	enum BOOLEAN t ;
	char sua ;
	float  x0[50] , x1[50] ;
	float a[50][50];

	clrscr();
	printf("PHUONG PHAP LAP POWER TIM TRI RIENG LON NHAT \n");
	printf("CAP MA TRAN n = ");
	scanf("%d",&n);
	printf("DOC SO LIEU MA TRAN A \n");
	for ( i = 0 ; i < n ; i++ )
	{
		printf("HANG THU %d : " , i);
		for ( j = 0 ; j < n ; j++ )		scanf("%f" , &a[i][j]);
	}
	t = true ;
	while ( t )
	{
		printf("CO SUA MA TRAN KHONG ? (c/k) : ");
		fflush(stdin);
		scanf("%c" , &sua );
		if ( toupper(sua) == 'C' )
		{
			printf("CHI SO HANG  i = ");
			fflush(stdin);
			scanf("%d" , &i);
			printf("CHI SO COT  j = ");
			fflush(stdin);
			scanf("%d" , &j);
			printf("a[%d,%d] =",i,j);
			fflush(stdin);
			scanf("%f" , &a[i][j]);
		}
		if ( toupper(sua) == 'K' ) t= false ;
	}
	printf("\tIN MA TRAN A\n");
	for (i = 0 ; i < n ; i++)
	{
		for (j = 0 ; j < n ; j++)	printf("%10.4f" , a[i][j]);
		printf("\n");
	}
	printf("DOC VECTOR BAN DAU x0\n");
	for (i = 0 ; i < n ; i++) 	scanf("%f" , &x0[i]) ;
	printf("SO BUOC LAP CHON TRUOC max = ");
	scanf("%d" , &max);
	printf("SAI SO CHON TRUOC epslon = ");
	scanf("%f" , &epslon);
	printf("\n");
	printf("THUC HIEN LAP\n");
	k = 1;
	t = false ;
	t1 = 0 ;
	do
	{
		t0 = t1 ;
		for (i = 0 ; i < n ; i++)
		{
			x1[i] = 0 ;
			for (j = 0 ; j < n ; j++)
				x1[i] += a[i][j] * x0[j] ;
		}
		printf("\n");
		s = 0.0 ;
		j = 0 ;
		for (i = 0 ; i < n ; i++)
			if ( s < fabs(x1[i]) )
			{
				j = i ;
				s += fabs(x1[i]) ;
			}
		t1 = x1[j] ;
		for (i = 0 ; i < n ; i++) x1[i] /= t1 ;
		if ( fabs(t1 - t0) < epslon )
		{
			printf("SO BUOC LAP DA THUC HIEN %d \n" , k);
			printf("\tTRI RIENG LON NHAT TMAX = %8.4f\n" , t1);
			printf("\tVECTOR RIENG TUONG UNG \n");
			for ( i = 0 ; i < n ; i++ )
				printf("x1[%d] = %f\n" , i , x1[i] );
			printf("\n");
			t = true ;
		}
		if ( fabs(t1 - t0) >= epslon )
		{
			for ( i = 0 ; i < n ; i++ )
				x0[i] = x1[i] ;
				k++ ;
		}
		if ( k > max )	t = true ;
	} while (!t) ;
	getch();
}