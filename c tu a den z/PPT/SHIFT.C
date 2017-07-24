/*Phuong phap SHIFT tim tri rieng gan nhat voi 1 gia tri cho truoc */

#include <stdio.h>
#include <conio.h>
#include <math.h>

enum BOOLEAN { false = 0 , true };

void main()
{
	int i , j , k , n , max , m;
	float  s , epslon , t0 , t1 , ts , max1 , c;
	enum BOOLEAN t , tn;
	char sua ;
	float  x0[50] , x1[50] ;
	float a[50][50] , b[50][50] , d[50][50];

	clrscr();
	printf("PHUONG PHAP LAP SHIFT TIM TRI RIENG GAN NHAT GIA TRI ts CHO TRUOC \n");
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
	tn = true ;
	while (tn)
	{
		printf("NHAP GIA TRI GAN GIA TRI RIENG CAN TINH ts =");
		fflush(stdin);
		scanf("%f" , &ts);
		printf("LAP MA TRAN D =A - ts.I\n");
		for (i = 0 ; i < n ; i++)
			for (j = 0 ; j < n ; j++)
			{
				if ( j != i) 	d[i][j] = a[i][j] ;
				if ( j == i) 	d[i][j] = a[i][j] -ts ;
			}
		printf("MA TRAN D \n");
		for (i = 0 ; i < n ; i++)
			{
				for (j = 0 ; j < n ; j++) printf("%6.3f\n" , d[i][j] );
				printf("\n");
			}
		printf("AN MOT PHIM DE TIEP TUC\n");
		getch();
		printf("LAP MA TRAN DAO B CUA D\n");
		for (i = 0 ; i < n ; i++)
			for (j = 0 ; j < n ; j++)
				if ( j == i) 	b[i][j] = 1 ;
				else b[i][j] = 0 ;
		i = 0 ;
		t = true;
		while (t)
		{
			if (d[i][i] == 0)
			{
				m = i ;
				max1 = 0 ;
				for (k = i + 1 ; k < n ; k++)
					if ( max1 < fabs(d[k][i]) )
					{
						m = k ;
						max1 = fabs(d[k][i]) ;
					}
				if ( m != i )
				{
					for (j = i ; j < n ; j++)
					{
						c = d[i][j] ;
						d[i][j] =  d[k][j] ;;
						d[k][j] = c;
					}
					for (j = 0 ; j < n ; j++)
					{
						c = b[i][j] ;
						b[i][j] =  b[k][j] ;
						b[k][j] = c;
					}
				}
				if ( m == i )
				{
					t = tn = false ;
					printf("MA TRAN D SUY BIEN\n");
				}
			} //END d[i][i] == 0
			if (d[i][i] != 0)
			{
				c = 1.0 / d[i][i] ;
				for (j = i + 1 ; j < n ; j++) 		d[i][j] *= c  ;
				for (j = 0 ; j < n ; j++) 		b[i][j] *= c  ;
				for (k = 0 ; k < n ; k++)
					if (k !=i )
					{
						s = d[k][i] ;
						for (j = i + 1 ; j < n ; j++) d[k][j] -= d[i][j]*s ;
						for (j = 0 ; j < n ; j++) b[k][j] -= b[i][j]*s ;
					}
				i++ ;
				if (i > (n-1) ) t = false ;
			} //end d[i][i] != 0
		}
		printf("DOC VECTOR BAN DAU x0\n");
		for (i = 0 ; i < n ; i++) 	scanf("%f" , &x0[i]) ;
		printf("SO BUOC LAP CHON TRUOC max = ");
		scanf("%d" , &max);
		printf("SAI SO CHON TRUOC epslon = ");
		scanf("%f" , &epslon);
		printf("\n");
		printf("THUC HIEN LAP VOI ts = %6.3f\n" , ts);
		printf("PHUONG PHAP SHIFT \n");
		printf("CHO MA TRAN A =\n");
		for (i = 0 ; i < n ; i++)
		{
			for (j = 0 ; j < n ; j++)	printf("%8.4f" , a[i][j]);
			printf("\n");
		}
		printf("TRI GAN TRI RIENG ts =%8.4f\n " , ts);
		printf("VECTOR DAU x0 =\n");
		for (i = 0 ; i < n ; i++) 	printf("  %6.3f" , x0[i]) ;
		printf("\n");
		printf("SAI SO epslon = %12.11f\n" , epslon);
		printf("MA TRAN D =\n");
		for (i = 0 ; i < n ; i++)
		{
			for (j = 0 ; j < n ; j++)	printf("  %10.4f" , d[i][j]);
			printf("\n");
		}
		printf("MA TRAN DAO CUA D, B=\n");
		for (i = 0 ; i < n ; i++)
		{
			for (j = 0 ; j < n ; j++)	printf("%10.4f" , b[i][j]);
			printf("\n");
		}
		k = 1 ;
		t = false ;
		t1 = 0 ;
		do
		{
			t0 = t1 ;
			for (i = 0 ; i < n ; i++)
			{
				x1[i] = 0 ;
				for (j = 0 ; j < n ; j++)
					x1[i] += b[i][j] * x0[j] ;
			}
			s = 0.0 ;
			j = 0 ;
			for (i = 0 ; i < n ; i++)
				if ( s < fabs(x1[i]) )
				{
					j = i ;
					s = fabs(x1[i]) ;
				}
			t1 = x1[j] ;
			for (i = 0 ; i < n ; i++)  	x1[i] /= t1 ;
			if ( fabs(t1 - t0) < epslon )
			{
				printf("SO BUOC LAP DA THUC HIEN k = %d\n " , k);
				t1 = 1.0/t1 ;
				t1 += ts ;
				printf("TRI RIENG GAN ts=%6.3f NHAT   t=%6.3f\n" ,ts , t1);
				printf("VECTOR RIENG TUONG UNG\n");
				printf("\tX =");
				for (i = 0 ; i < n ; i++)  	printf("  %f" , x1[i] );
				printf("\n");
				t = true ;
			}
			if ( fabs(t1 - t0) >= epslon )
			{

				for (i = 0 ; i < n ; i++)  	x0[i] = x1[i] ;
				k++ ;
			}
			if (k > max )	t = true ;
		} while (!t) ;
		printf("CO TINH ts KHAC KHONG ?(c/k) :");
		scanf("%c" , &sua);
		if ( toupper(sua) != 'C') 	tn = false ;
	}
	getch();
}