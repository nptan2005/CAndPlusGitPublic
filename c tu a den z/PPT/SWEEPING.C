/*Phuong phap lap SWEEPING tinh cac tri rieng khac cua ma tran doi xung A*/
#include <stdio.h>
#include <conio.h>
#include <math.h>

enum BOOLEAN { false = 0 , true };

void main()
{
	int i , j , k , n , max , ik;
	float  s , epslon , t0 , t1 , c;
	enum BOOLEAN t , tik;
	char sua ;
	float  x0[50] , x1[50] , y[50] , lamda[50];
	float a[50][50] , b[50][50] , v[50][50];

	clrscr();
	printf("PHUONG PHAP LAP SWEEPING TIM CAC TRI RIENG CUA MA TRAN DOI XUNG \n");
	printf("CAP MA TRAN n = ");
	scanf("%d",&n);
	printf("DOC SO LIEU MA TRAN A \n");
	for ( i = 0 ; i < n ; i++ )
	{
		printf("HANG THU %d : " , i);
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
		for (j = 0 ; j < n ; j++)	printf("%10.4f" , a[i][j]);
		printf("\n");
	}
	printf("DOC VECTOR BAN DAU x0\n");
	for (i = 0 ; i < n ; i++) 	scanf("%f" , &x0[i]) ;
	printf("SO BUOC LAP CHON TRUOC max = ");
	scanf("%d" , &max);
	printf("SAI SO CHON TRUOC epslon = ");
	scanf("%f" , &epslon);
	printf("\n");
	printf("THUC HIEN LAP\n");
	ik = 0;
	tik = true ;
	t = false ;
	while (tik)
	{
		k = 0 ;
		t = false ;
		t1 = 0 ;
		for (i = 0 ; i < n ; i++) 	x1[i] = x0[i] ;
		do
		{
			t0 = t1 ;
			for (i = 0 ; i < n ; i++)
			{
				y[i] = 0 ;
				for (j = 0 ; j < n ; j++)
					y[i] += a[i][j] * x1[j] ;
			}
			s = 0.0 ;
			j = 0 ;
			for (i = 0 ; i < n ; i++)
				if ( s < fabs(y[i]) )
				{
					j = i ;
					s += fabs(y[i]) ;
				}
			t1 = y[j] ;
			for (i = 0 ; i < n ; i++)  	y[i] /= t1 ;
			if ( fabs(t1 - t0) < epslon )
			{
				lamda[ik] = t1 ;
				for (i = 0 ; i < n ; i++)  	v[i][ik] = y[i] ;
				c = 0 ;
				for (i = 0 ; i < n ; i++)  	c += y[i] * y[i] ;
				c = t1 / c ;
				for (i = 0 ; i < n ; i++)
					for (j = 0 ; j < n ; j++ )	 b[i][j] = y[i] * y[i] ;
				for (i = 0 ; i < n ; i++)
					for (j = 0 ; j < n ; j++ )	 a[i][j] -= b[i][j];
				printf("MA TRAN D%d :\n" , ik);
				for ( i = 0 ; i < n ; i++ )
				{
					for ( j = 0 ; j < n ; j++ )	   printf("%8.4f" , a[i][j]);
					printf("\n");
				}
				t = true ;
				ik++ ;
				if ( ik > n - 1 )
				{
					tik = false ;
					printf("\n");
					printf("CAC TRI RIENG VA VECTOR RIENG\n ");
					printf("lamda\t x1 \t x2 \t x3 \n");
					for ( i = 0 ; i < n ; i++ )
					{
						printf("%8.4f" , lamda[i]) ;
						for ( j = 0 ; j < n ; j++ )
							printf(" %8.4f" , v[i][j]);
						printf("\n");
					}
				}
			}
			if ( fabs(t1 - t0) >= epslon )
			{
				for ( i = 0 ; i < n ; i++ ) x1[i] = y[i] ;
				k++ ;
				if ( k > max )
				{
					t = true ;
					tik = false ;
					printf("PHEP LAP KHONG HOI TU \n");
					printf("k =%d , ik =%d\n" , k , ik);
				}
			}
		} while (!t) ;
	}
	getch();
}