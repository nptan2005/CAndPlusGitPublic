/*GAUSS-SKYLINE*/
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
	int ma[50] , mb[50];
	float am[2500] ;

	clrscr();
	printf("GIAI HE SKYLINE \n");
	printf("SO PHUONG TRINH n = ");
	scanf("%d",&n);
	for ( j = 0 ; j < n ; j++ )
	{
		printf("CHI SO HANG PHAN TU <>0 DAU TIEN ");
		printf("TRONG COT %d" , j);
		printf(" I = ");
		scanf("%d" , &mb[j]);
	}
	t = true ;
	while (t)
	{
		printf("CO SUA CHI SO HANG KHONG ?(c/k) : ");
		fflush(stdin);
		scanf("%c" , &sua );
		if ( toupper(sua) == 'C' )
		{
			printf("COT J= ");
			fflush(stdin);
			scanf("%d" , &j);
			printf("CHI SO HANG  I = ");
			fflush(stdin);
			scanf("%d" , &mb[j]);
		}
		if ( toupper(sua) == 'K' ) 	t= false ;
	}
	k = 0 ;
	k1 = 0 ;
	printf("DOC A THEO COT TU DUONG CHEO CHINH LEN\n");
	printf("CHI DOC TAM GIAC TREN\n");
	for ( j = 0 ; j < n ; j++ )
	{
		k1= k +1 ;
		ma[j] = k1 ;
		printf("COT THU %d " , j);
		for ( i = j ; i >= mb[j] ; j-- )
		{
			k++ ;
			scanf("%f" , am[k] ) ;
		}
	}
	t = true ;
	while (t)
	{
		printf("CO SUA MA TRAN A KHONG ?(c/k) : ");
		fflush(stdin);
		scanf("%c" , &sua );
		if ( toupper(sua) == 'C' )
		{
			printf("CHI SO HANG  i= ");
			fflush(stdin);
			scanf("%d" , &i);
			printf("CHI SO COT  j= ");
			fflush(stdin);
			scanf("%d" , &j);
			k = ma[j] + j - i ;
			printf("A[i,j] = ");
			scanf("%f" , &c);
			am[k] = c ;
		}
		if ( toupper(sua) == 'K' ) 	t= false ;
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
			scanf("%f" , &c);
			b[i] = c ;
		}
	}
	printf("\tVE PHAI B\n");
	for (i = 0 ; i < n ; i++) printf("%8.4f" , b[i]);
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
				if (i >= mb[k])
				{
					k1 = ma[i] + k - i ;
					c = am[k1] / am[ma[i]] ;
					for (j = k ; j < n ; j++)
					{
						k2 = ma[j] + j - k ;
						k3 = ma[j] + j -i ;
						am[k2] =am[k2] - am[k3] * c ;
					}
					b[k] -= b[i] * c;
					am[k1] /=  am[ma[i]];
				}
			b[i] /= am[ma[i]] ;
			i++ ;
		}
		if ( i == n - 1 )	t = false ;
	}
	if (i == n - 1 )
	{
		b[n-1] /= am[ma[n]] ;
		for ( i = n - 2 ; i >= 0 ; i-- )
			for ( j = i + 1 ; j < n ; j++ )
			{
				k = ma[j] + j - i ;
				b[i] -= am[k] * b[j] ;
			}
			printf("\tNGHIEM CUA HE\n\n");
			for ( i = 0 ; i < n ; i++ )
				printf("x[%d] = %f\n" , i , b[i] );
	}
	getch();
}