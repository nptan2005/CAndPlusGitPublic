/*Chuong trinh tinh tich he so cua da thuc dac trung FADEEV-LEVERIER */
#include <stdio.h>
#include <conio.h>
#include <math.h>

enum BOOLEAN { false = 0 , true };

void main()
{
	int i , j , k , m ,n , k1 ;
	float  c1 ,d , vet ;
	enum BOOLEAN t ;
	char sua ;
	float p[50] ;
	float a[50][50] , b[50][50] , c[50][50] , b1[50][50];

	clrscr();
	printf("\t\tFADEEV-LEVERIER\n");
	printf("LAP DA THUC DAC TRUNG\n");
	printf("CAP MA TRAN n =");
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
		printf("CO SUA SO LIEU KHONG ? (c/k) : ");
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
	printf("LAP MA TRAN PHU B\n");
	for (i = 0 ; i < n ; i++)
		for ( j = 0 ; j < n ; j++)	 b[i][j] = a[i][j];
	printf("PHAN CHINH CUA CHUONG TRINH\n");
	for (k = 0 ; k < n - 2 ; i++)
	{
		vet = 0.0 ;
		for (i = 0 ; i < n ; i++) vet += b[i][i] ;
		p[k] = vet / (1.0 * k) ;
		printf("k =%d , p[k] =%10.4f\n" , k , p[k]);
		getch();
		printf("LAP MA TRAN PHU C = (B - P[k].E)\n");
		for (i = 0 ; i < n ; i++)
			for ( j = 0 ; j < n ; j++)
			{
				if(j != i)	 c[i][j] = b[i][j];
				if(j == i)	 c[i][j] = b[i][j] - p[k];
			}
		for (i = 0 ; i < n ; i++)
			for ( j = 0 ; j < n ; j++)
			{
				b[i][j] = 0;
				for (k1 = 0 ; k1 < n ; i++)
					b[i][j] += a[i][k1] * c[k1][j] ;
			}
	}
	vet = 0;
	for (i = 0 ; i < n ; i++) 	vet += b[i][i] ;
	p[n-1] = vet / ( 1.0 * (n-1) );
	printf("CAC HE SO CUA DA THUC DAC TRUNG\n");
	printf("\n");
	d = 1.0 ;
	printf("%6.2f" , d);
	for (i = 0 ; i < n ; i++)
	{
		c1 = -p[i] ;
		printf(" %6.2f" , c1);
	}
	printf("\n");
	printf("MA TRAN DAO CUA MA TRAN A\n");
	c1 = 1.0 / p[n-1] ;
	for (i = 0 ; i < n ; i++)
	{
		for ( j = 0 ; j < n ; j++)
		{
			c[i][j] *= c1 ;
			printf("%5.2f" , c[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("KIEM TRA TICH A.A-1\n");
	printf("\n");
	for (i = 0 ; i < n ; i++)
	{
		for ( j = 0 ; j < n ; j++)
		{
			d = 0 ;
			for ( k1 = 0 ; k1 < n ; k1++)
				d += a[i][k1] * c[k1][j] ;
			printf("%5.2f" , d);
		}
		printf("\n");
	}
	getch();
}