/*Phuong phap noi suy Newton voi cac khoang  chia deu*/
#include <stdio.h>
#include <conio.h>
#include <math.h>

enum BOOLEAN { false = 0 , true };

void main()
{
	int i , j , k , n , m;
	float   xt , xs , s , h ;
	enum BOOLEAN t ;
	char sua ;
	float  x[52] , y[52] , y1[50];
	float y2[1000] , x1[1000] ;
	float a[50][50] ;

	clrscr();
	printf("PHUONG PHAP NOI SUY NEWTON \n");
	printf("SO MAU QUAN SAT n = ");
	scanf("%d",&n);
	fflush(stdin) ;
	printf("DOC CAC DIEM QUAN SAT X[i](i = 0,n)\n");
	for ( i = 0 ; i <= n ; i++ ) scanf("%f" , &x[i]);
	printf("DOC CAC KET QUA QUAN SAT Y[i](i = 0,n)\n");
	for ( i = 0 ; i <= n ; i++ ) scanf("%f" , &y[i]);
	printf("SO DIEM CAN TINH m = ");
	scanf("%d" , &m);
	printf("KHOANG CHIA DEU KHONG ? (y/n)\n");
	fflush(stdin);
	scanf("%c" , &sua );
	if ( toupper(sua) == 'N' )
	{
		printf("DOC CAC GIA TRI X CAN TINH \n ");
		for ( i = 0 ; i < m ; i++ ) scanf("%f" , &x1[i]);
	}
	if ( toupper(sua) == 'Y' )
	{
		h = (x[n] - x[0])/(1.0*m) ;
		x1[0] = x[0] + h ;
		for ( i = 1 ; i < m ; i++ )  x1[i] = x[i-1] + h ;;
	}
	printf("CAC MAU QUAN SAT \n");
	printf("X =");
	for ( i = 0 ; i <= n ; i++ ) 	printf(" %8.3f" , x[i]);
	printf("\n");
	printf("Y =");
	for ( i = 0 ; i <= n ; i++ ) 	printf(" %8.3f" , y[i]);
	printf("\n");
	for ( i = 0 ; i < n ; i++ )
//		a[i][0] = (y[i + 1] - y[i])/(x[i + 1] - x[i]) ;
		y1[i] = (y[i + 1] - y[i])/(x[i + 1] - x[i]) ;
	for ( j = 1 ; j < n ; i++ )
		for ( i = n - 1 ; i >= j ; i-- )
//		a[i][j] = (a[i + 1][j - 1] - a[i][j - 1])/(x[i + 1] - x[i + 1 -j]) ;
		y1[i] = (y1[i] - y1[i -1])/(x[i + 1] - x[i + 1 - j]) ;





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

	t = true ;
	while ( t )
	{
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
	printf("\tCHEO HOA DANG TOAN PHUONG VOI MA TRAN A\n");
	for (i = 0 ; i < n ; i++)
	{
		for (j = 0 ; j < n ; j++)	printf("  %10.3f" , a[i][j]);
		printf("\n");
	}
	t = true ;
	k = 0 ;
	printf("NHAN 1 PHIM BAT KY DE TIEP TUC\n");
	getch();
	while (t)
	{
		if (a[k][k] == 0)
		{
			t = false ;
			printf("A[k][k] =0 \n");
		}
		if (a[k][k] != 0)
		{
			c = 1.0/ a[k][k] ;
			for (i = k + 1 ; i < n ; i++)
			{
				a[i][i] -= a[k][i]*a[k][i]*c ;
				for (j = i + 1 ; j < n ; j++)
					a[i][j] -= a[k][i]*a[k][j]*c ;
			}
		}
		printf("\tMA TRAN SAU LAN BIEN DOI THU %d\n" , k);
		for (i = 0 ; i < n ; i++)
		{
			for (j = 0 ; j < n ; j++)   printf("    %f" , a[i][j]);
			printf("\n") ;
		}
		k++ ;
		if (k == n - 1 ) 	t = false ;
	}
	if (k == n - 1 )
	{
		printf("DAO CUA MA TRAN CHUYEN CO SO T \n");
		for (i = 1 ; i < n ; i++)
			for (j = 0 ; j <= i - 1  ; j++) a[i][j] = a[j][i] ;
		printf("\n") ;
		for (i = 0 ; i < n ; i++)
		{
			for (j = 0 ; j < n ; j++)	printf("    %5.2f" , a[i][j]);
			printf("\n") ;
		}
		for (i = 0 ; i < n - 1 ; i++ )    b[i] = 1.0/a[i][i];
		b[n] = a[n][n];
		printf("\n") ;
		printf("DANG CHEO CUA DANG TOAN PHUONG\n");
		printf("\n") ;
		printf(" f(y,y) =") ;
		printf("  %15.13f*y0" , b[0]) ;
		for (i = 1 ; i < n ; i++ )
			if  (b[i] != 0)
			{
				if  (b[i] > 0) 	printf("  +%15.13f*y%d" , b[i] , i) ;
				else printf("  %15.13f*y%d" , b[i] , i) ;
			}
		printf("\n") ;
		printf("\tPHEP BIEN DOI TOA DO\n");
		printf("\n") ;
		for (i = 0 ; i < n ; i++ )
		{
			printf(" y%d =" ,i) ;
			for (j = i ; j < n  ; j++)
			{
				if ( j == i )	printf("  %8.4f*x%d" , a[i][j] , i) ;
				else
					if (a[i][j] != 0 )
					{
						if (a[i][j] > 0 )
							printf("  +%6.4f*x%d" , a[i][j] , j) ;
						else  printf("  %8.4f*x%d" , a[i][j] , j) ;
					}
				}
				printf("\n") ;
			}
	}
	getch();
}