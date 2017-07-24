/*Noi suy LAGRANGE*/
#include <stdio.h>
#include <conio.h>


void main()
{
	int i , j , k , k1 , n , m;
	float   s1 , s , h ;
	char sua ;
	float  x[52] , x0[52] , y0[52];
	float y1[1000] , x1[1000] ;

	clrscr();
	printf("PHUONG PHAP NOI SUY \n");
	printf("SO MAU QUAN SAT n = ");
	scanf("%d",&n);
	fflush(stdin) ;
	printf("DOC CAC DIEM QUAN SAT X[i]  (i = 0,n)\n");
	for ( i = 0 ; i <= n ; i++ ) scanf("%f" , &x0[i]);
	printf("DOC CAC KET QUA QUAN SAT Y[i]  (i = 0,n)\n");
	for ( i = 0 ; i <= n ; i++ ) scanf("%f" , &y0[i]);
	printf("TINH MAU SO CUA Rk(x) = x[k] (k = 0,n)\n");
	for ( k = 0 ; k <= n ; k++ )
	{
		s1 = 1 ;
		for ( i = 0 ; i <= n ; i++ )
			if ( i!= k ) 	s1 *= x0[k] - x0[i] ;
		x[k] = s1 ;
	}
	printf("\n");
	printf("SO DIEM CAN TINH m = ");
	scanf("%d" , &m);
	printf("KHOANG CHIA DEU KHONG ? (y/n)\n");
	fflush(stdin);
	scanf("%c" , &sua );
	if ( toupper(sua) == 'N' )
	{
		printf("DOC %d DIEM CAN TINH \n " , m);
		for ( i = 0 ; i < m ; i++ ) scanf("%f" , &x1[i]);
	}
	if ( toupper(sua) == 'Y' )
	{
		h = (x0[n] - x0[0])/(1.0*m) ;
		x1[0] = x0[0] + h ;
		for ( i = 1 ; i < m ; i++ )  x1[i] = x1[i-1] + h ;
	}
	printf("TINH y1[k1] = Pn(x1[k1] \n");
	for ( k1 = 0 ; k1 < m ; k1++ )
	{
		s = 0 ;
		for ( k = 0 ; k <= n ; k++ )
		{
			s1 = 1 ;
			for ( i = 0 ; i <= n ; i++ )
				if (i != k) s1 *= x1[k1] - x0[i] ;
			s += y0[k]*s1/x[k] ;
		}
		y1[k1] = s ;
	}
	printf("CAC MAU QUAN SAT \n");
	printf("X0 =");
	for ( i = 0 ; i <= n ; i++ ) 	printf("  %f" , x0[i]);
	printf("\n");
	printf("Y0 =");
	for ( i = 0 ; i <= n ; i++ ) 	printf("  %f" , y0[i]);
	printf("\n");
	getch();
	printf("KET QUA NOI SUY CHO %d DIEM CAN TINH \n" , m);
	printf("        X[i]                P(X[i])\n");
	printf("\n");
	for ( i = 0 ; i < m ; i++ )
		printf("x[i] =%8.4f       P(x[i]) =%8.4f\n" , x1[i] , y1[i]);
	getch();
}
