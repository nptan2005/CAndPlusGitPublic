/*Noi suy bang phuong phap lap AIKEN-NEVILLE */
#include <stdio.h>
#include <conio.h>

enum BOOLEAN { false = 0 , true };

void main()
{
	int i , j , k , n , m;
	float   xt , xs , s , h ;
	enum BOOLEAN t ;
	char sua ;
	float  x[52] , x0[52] , y[52] , y0[52];
	float y1[1000] , x1[1000] ;

	clrscr();
	printf("PHUONG PHAP NOI SUY AITKEN-NEVILLE \n");
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
		printf("DOC CAC m DIEM CAN TINH \n ");
		for ( i = 0 ; i < m ; i++ ) scanf("%f" , &x1[i]);
	}
	if ( toupper(sua) == 'Y' )
	{
		h = (x0[n] - x0[0])/(1.0*(m + 1)) ;
		x1[0] = x0[0] + h ;
		for ( i = 1 ; i < m ; i++ )  x1[i] = x1[i-1] + h ;;
	}
	printf("CAC MAU QUAN SAT \n");
	printf("X0 =");
	for ( i = 0 ; i <= n ; i++ ) 	printf("  %f" , x0[i]);
	printf("\n");
	printf("Y0 =");
	for ( i = 0 ; i <= n ; i++ ) 	printf("  %f" , y0[i]);
	printf("\n");
	for ( k = 0 ; k < m ; k++ )
	{
		for ( i = 0 ; i <= n ; i++ ) 	y[i] = y0[i];
		for ( i = 0 ; i <= n ; i++ ) 	x[i] = x1[k] - y0[i] ;
		for ( j = 0 ; j <= n ; j++ )
			for ( i = n ; i >= j ; i-- )
				y[i] = (x[j - 1]*y[i] - x[i]*y[j - 1])/(x0[i] - x0[j - 1]);
		y1[k] = y[n] ;
	}
	printf("          DOI x CAN TINH                  KET QUA P(x)\n");
	printf("\n");
	for ( k = 0 ; k < m ; k++ )
		printf("x =%8.4f       P(x) =%8.4f\n" , x1[k] , y1[k]);
	getch();
	getch();
}
