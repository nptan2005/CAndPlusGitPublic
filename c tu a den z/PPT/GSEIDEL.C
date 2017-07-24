/*GAUSS-SEIDEL*/
#include <stdio.h>
#include <conio.h>
#include <math.h>

enum BOOLEAN { false = 0 , true };

void main()
{
	int i , j , k , n , max ;
	float  c , s , epslon;
	enum BOOLEAN t ;
	char sua ;
	float b[50] , x0[50] , x1[50] ;
	float a[50][50];

	clrscr();
	printf("PHUONG PHAP LAP GAUSS-SEIDEL GIAI HE  \n");
	printf("SO PHUONG TRINH n = ");
	scanf("%d",&n);
	printf("DOC SO LIEU MA TRAN A \n");
	for ( i = 0 ; i < n ; i++ )
	{
		printf("HANG THU %d" , i);
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
		for (j = 0 ; j < n ; j++)	printf("%10.3f" , a[i][j]);
		printf("\n");
	}
	printf("DOC VE PHAI B\n");
	for (i = 0 ; i < n ; i++) scanf("%f" , b[i]);
	t = true ;
	while (t)
	{
		printf("CO SUA VE PHAI B KHONG ?(c/k) : ");
		fflush(stdin);
		scanf("%c" , &sua);
		if (toupper(sua) == 'K')	t = false ;
		if (toupper(sua) == 'C')
		{
			printf("Chi so hang i = ");
			scanf("%d" , &i);
			printf("b[%d] = ",i);
			scanf("%f" , &b[i]);
		}
	}
	printf("\tIN VE PHAI B\n");
	for (i = 0 ; i < n ; i++) printf("%8.4f\n" , b[i]);
	printf("\n");
	printf("DOC VECTOR BAN DAU x0\n");
	for (i = 0 ; i < n ; i++) scanf("%f" , &x0[i]);
	printf("VECTOR BAN DAU x0 \n");
	for (i = 0 ; i < n ; i++) printf("%10.4f" , x0[i]);
	printf("LAP MA TRAN A*\n");
	for (i = 0 ; i < n ; i++)
	{
		c = 1.0 / a[i][i] ;
		for (j = 0 ; j < n ; j++)
			if (j != i) a[i][j] *=c ;
		b[i] *= c ;
		a[i][i] = 0 ;
	}
	printf("MA TRAN A*\n");
	for (i = 0 ; i < n ; i++)
		for (j = 0 ; j < n ; j++) 	printf("%10.4f\n" , a[i][i] );
	printf("SO BUOC LAP NHIEU NHAT max = ");
	scanf("%d" , &max);
	printf("SAI SO DO BUOC CHON TRUOC epslon = ");
	scanf("%f" , &epslon);
	printf("\n");
	printf("SO BUOC LAP CHON max = %d\n" , max);
	printf("SAI SO DA CHON epslon = %f\n" , epslon);
	printf("THUC HIEN LAP\n");
	k = 1 ;
	t = false ;
	do
	{
		for (i = 0 ; i < n ; i++)
		{
			x1[i] = b[i] ;
			for (j = 0 ; j < n ; j++)
				if (j < i - 1 )		x1[i] -= a[i][j] * x1[j] ;
				else  x1[i] -= a[i][j] * x0[j] ;
		}
		printf("\n");
		printf("X SAU LAN KHU %d\n" , k);
		for (i = 0 ; i < n ; i++) 	printf("%10.4f\n" , x1[i]) ;
		s = 0.0 ;
		for (i = 0 ; i < n ; i++)  s += fabs(x1[i] - x0[i]) ;
		if (s >= epslon)
			for (i = 0 ; i < n ; i++) 	x0[i] = x1[i] ;
		if (s < epslon)
		{
			t = true ;
			printf("\n");
			printf("PHEP LAP HOI TU SAU %d BUOC\n" , k);
			printf("\tNGHIEM CUA HE\n");
			for ( i = 0 ; i < n ; i++ )
				printf("x[%d] = %f\n" , i , x1[i] );
		}
		k++ ;
		if ( k > max )
		{
			t = true ;
			printf("%12.6f" , s );
			printf("LAP KHONG HOI TU SAU %d \nBUOC\n" , k - 1);
		}
	} while(!t);
	getch();
}