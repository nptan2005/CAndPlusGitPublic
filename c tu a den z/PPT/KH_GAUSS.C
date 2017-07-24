/*Phuong phap khu Gauss giai he doi xung chi su dung phan tam giac tren*/
#include <stdio.h>
#include <conio.h>
#include <math.h>

enum BOOLEAN { false = 0 , true };

void main()
{
	int i , j , k , n ;
	float  c ;
	enum BOOLEAN t ;
	char sua ;
	float b[50] ;
	float a[50][50];

	clrscr();
	printf("PHUONG PHAP KHU GAUSS GIAI HE DOI XUNG\n");
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
	t = true ;
	i = 0 ;
	while (t)
	{
		if (a[i][i] == 0)
		{
			t = false ;
			printf("A[%d,%d] = 0 " , i , i );
		}
		if (a[i][i] != 0)
		{
			for (k = i + 1 ; k < n ; k++)
			{
				c = a[i][k] / a[i][i] ;
				for (j = k ; j < n ; j++)
					a[k][j] -= a[i][j] * c ;
				b[k] -= b[i] * c;
				a[i][k] /= a[i][i] ;
			}
			b[i] /= a[i][i] ;
			printf("MA TRAN (A,B)\n");
			printf("SAU LAN KHU HANG %d\n" , i);
			for ( k = 0 ; k < n ; k++)
			{
				for ( j = 0 ; j < n ; j++) printf("%8.4f" , a[k][j]);
				printf("%8.4f" , b[k]);
				printf("\n");
			}
			i++;
		}
		if ( i == n - 1 )	t = false ;
	}
	if (i == n - 1)
	{
		b[n-1] /= a[n - 1][n - 1] ;
		for ( i = n - 2 ; i >= 0 ; i-- )
			for ( j = i + 1 ; j < n ; j++ )
				b[i] -= a[i][j] * b[j] ;
		printf("\tNGHIEM CUA HE\n\n");
		for ( i = 0 ; i < n ; i++ )
			printf("x[%d] = %8.4f\n" , i , b[i] );
	}
	getch();
}