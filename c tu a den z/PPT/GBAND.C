/*BAND*/
#include <stdio.h>
#include <conio.h>

enum BOOLEAN { false = 0 , true };

void main()
{
	int i , j , k , n , r , m ;
	float c ;
	enum BOOLEAN t ;
	char sua ;
	float b[50] ;
	float am[20][50] ;

	clrscr();
	printf("GIAI HE BANK DOI XUNG \n");
	printf("SO PHUONG TRINH n = ");
	scanf("%d" , &n);
	printf("DO RONG CUA BANK R = ");
	scanf("%d" , &r);
	printf("DOC PHAN TAM GIAC TREN CUA MA TRAN BANK A \n");
	for ( i = 0 ; i < n ; i++ )
	{
		if ( (i + r - 1) < n )	m = i + r - 1 ;
		else m = n - 1 ;
		for ( j = i ; j >= m ; j++) 	scanf("%f" , &am[i][j-i+1]);
	}
	t = true ;
	while (t)
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
			scanf("%f" , &am[i][j - i + 1]);
		}
		if ( toupper(sua) == 'K' ) t= false ;
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
			printf("Chi so i = ");
			scanf("%d" , &i);
			printf("B[%d] = ",i);
			scanf("%f" , &b[i]);
		}
	}
	t = true ;
	i = 0 ;
	while (t)
	{
		if (am[i][0] == 0)
		{
			t = false ;
			printf("A[%d,%d] = 0 " , i , i );
		}
		if (am[i][0] != 0)
		{
			if ( (i + r - 1) < n )	m = i + r - 1 ;
			else m = n-1 ;
			for (k = i + 1 ; k <= m ; k++)
				if (am[i][k - i + 1] != 0)
				{
					c = am[i][k - i + 1] / am[i][0] ;
					for (j = k ; j <= m ; j++)
						am[k][j - k + 1] += am[i][j - i + 1] * c ;
					b[k] -= b[i] * c;
					am[i][k - i + 1] /= am[i][0] ;
				}
			b[i] /= am[i][0] ;
			i++ ;
		}
		if ( i == n - 1 )	t = false ;
	}
	if (i == n - 1 )
	{
		b[n-1] /= am[n - 1][0] ;
		for ( i = n - 2 ; i >= 0 ; i-- )
		{
			if ( (i + r - 1) < n ) 	m = i + r - 1 ;
			else m = n - 1 ;
			for ( j = i + 1 ; j <= m ; j++ )
				b[i] -= am[i][j - i + 1] * b[j] ;
		}
		printf("\tNGHIEM CUA HE\n\n");
		for ( i = 0 ; i < n ; i++ )
			printf("x[%d] = %f\n" , i , b[i] );
	}
	getch();
}