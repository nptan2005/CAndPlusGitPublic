/*GausM1*/
#include <stdio.h>
#include <conio.h>

enum BOOLEAN { false = 0 , true };

void main()
{
	int i , j , k , k1 , k2 , k3 , n ;
	float  c ;
	enum BOOLEAN t ;
	char sua ;
	float b[50] ;
	int ma[50];
	float am[50];

	clrscr();
	printf("GIAI HE DOI XUNG DUNG MANG 1 CHIEU \n");
	printf("SO PHUONG TRINH n = ");
	scanf("%d",&n);
	printf("DOC MA TRAN A PHAN TAM GIAC TREN \n");
	k = 0 ;
	k1 = 0 ;
	for ( i = 0 ; i < n ; i++ )
	{
		k1++ ;
		ma[i] = k1 ;
		printf("HANG THU %d" , i);
		for ( j = 0 ; j < n ; j++ )
		{
			k++;
			scanf("%f" , &am[k]);
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
				k = ma[i] + j - i ;
				printf("a[%d,%d] =",i,j);
				fflush(stdin);
				scanf("%f" , &am[k]);
			}
			if ( toupper(sua) == 'K' ) t= false ;
		}
		k = 0 ;
		printf("\tMA TRAN A\n");
		for (i = 0 ; i < n ; i++)
		{
			k++;
			printf("%10.3f" , am[k]);
		}
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
			printf("Chi so i = ");
			scanf("%d" , &i);
			printf("B[%d] = ",i);
			scanf("%f" , &b[i]);
		}
	}
	printf("\tVECTOR VE PHAI B\n");
	for (i = 0 ; i < n ; i++) printf("%8.4f" , b[i]);
	printf("\n");
	t = true ;
	i = 0 ;
	while (t)
	{
		if (am[ma[i]] == 0)
		{
			t = false ;
			printf("A[%d,%d] = 0 " , i , j );
		}
		if (am[ma[i]] != 0)
		{
			for (k = i + 1 ; k < n ; k++)
			{
				k1 = ma[i] + k - i ;
				c = am[k1] / am[ma[i]] ;
				for (j = k ; j < n ; j++)
				{
					k2 = ma[k] + j - k ;
					k3 = ma[i] + j -i ;
					am[k2] =am[k2] - am[k3] * c ;
				}
				am[k1] = c ;
				b[k] -= b[i] * c;
			}
			b[i] /= am[ma[i]] ;
		}
		i++ ;
		if ( i == n - 1 )	t = false ;
	}
	if (i == n - 1 )
	{
		b[n-1] /= am[ma[n]] ;
		for ( i = n - 2 ; i >= 0 ; i-- )
			for ( j = i + 1 ; j < n ; j++ )
			{
				k = ma[i] + j - i ;
				b[i] -= am[k] * b[j] ;
			}
			printf("\tNGHIEM CUA HE\n\n");
			for ( i = 0 ; i < n ; i++ )
				printf("x[%d] = %f\n" , i , b[i] );
	}
	getch();
}