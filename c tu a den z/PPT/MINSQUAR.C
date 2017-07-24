/*PHUONG PHAP BINH PHUONG TOI THIEU CHO HE HAM DA THUC*/
#include <stdio.h>
#include <conio.h>


void main()
{
	int i , j , kp , n , m , p , k;
	float   sx , s1 , s , c , d ;
	char sua ;
	float  x[52] , y[52];
	float y1[51] ;
	double b[51][51] ;

	clrscr();
	printf("PHUONG PHAP BINH PHUONG TOI THIEU  \n");
	printf("TINH CAC THAM SO CUA HAM THUC NGHIEM\n");
	printf("CHO HE HAM LA CAC DA THUC\n");
	printf("SO MAU QUAN SAT n = ");
	scanf("%d",&n);
	fflush(stdin) ;
	printf("DOC CAC DIEM QUAN SAT X[i]  (i = 0,n)\n");
	for ( i = 0 ; i < n ; i++ ) scanf("%f" , &x[i]);
	printf("DOC CAC KET QUA QUAN SAT Y[i]  (i = 0,n)\n");
	for ( i = 0 ; i < n ; i++ ) scanf("%f" , &y[i]);
	printf("CAC MAU QUAN SAT \n");
	printf("X =");
	for ( i = 0 ; i < n ; i++ ) 	printf("  %f" , x[i]);
	printf("\n");
	printf("Y =");
	for ( i = 0 ; i < n ; i++ ) 	printf("  %f" , y[i]);
	printf("\n");
	printf("SO THAM SO m = ");
	scanf("%d" , &m);
	printf("XAY DUNG MA TRAN B VA VE PHAI Y1\n");
	for ( p = 0 ; p <= m ; p++ )
	{
		y1[p] = 0 ;
		for ( i = 0 ; i < n ; i++ )
		{
			sx = 1 ;
			for ( j = 0 ; j < p ; j++ ) sx *= x[i] ;
			y1[p] += y[i]*sx ;
		}
	}
	for ( p = 0 ; p <= m ; p++ )
		for ( k = p ; k <= m ; k++ )
		{
			kp = k + p ;
			b[p][k] = 0 ;
			for ( i = 1 ; i <= n ; i++ )
			{
				sx = 1 ;
				for ( j = 0 ; j < kp ; j++ ) sx *= x[i] ;
				b[p][k] += sx ;
			}
		}
	printf("PHAN TAM GIAC TREN CUA B VA VE PHAI Y1\n");
	for ( i = 0 ; i <= m ; i++ )
	{
		for ( j = 0 ; j <= m ; j++ ) 	printf("  %lf", b[i][j]);
		printf("  %lf", y1[i]);
		printf("\n");
	}
//	printf("GIAI HE DOI XUNG TIM CAC THAM SO a0,a1,...,am\n");
	for ( i = 0 ; i < m ; i++ )
	{
		c = 1.0/b[i][i] ;
		for ( k = i + 1 ; k <= m ; k++ )
		{
			d = b[i][k] ;
			for ( j = i + 1 ; j <= m ; j++ ) 	b[k][j] -=b[i][j]*c*d ;
			y1[k] -= y1[i]*c*d ;
			b[i][k] *= c ;
		}
		y1[i] *= c ;
	}
	printf("TINH CAC THAM SO a0,a1,...,am\n");
	y1[m] /= b[m][m] ;
	for ( i = m -1 ; i >= 0 ; i-- )
		for ( j = i + 1 ; j <= m ; j++ )	y1[i] -= b[i][j]*y1[j] ;
	printf("CAC THAM SO CAN TIM\n");
	for ( i = 0 ; i <= m ; i++ )	printf("a[%d] =%f\n" , i , y1[i]);
	getch();
}
