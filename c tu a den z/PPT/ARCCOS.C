#include <stdio.h>
#include <math.h>

#define DOMAIN		1
#define SING		2
#define OVERFLOW	3	/* overflow error */
#define UNDERFLOW	4	/* underflow error */
#define TLOSS		5
#define PLOSS		6
#define EDOM		33
#define ERANGE		34
#define MIEEE 1
#define VOLATILE 
#define XPD 0,
#define NANS
#define INFINITY
void mtherr();

static short P[24] = {
0x8ad3,0x0bd4,0x6b9b,0x3f71,
0x5c16,0x333e,0x4341,0xbfe3,
0x2dd9,0x178a,0xc74b,0x4015,
0x907b,0xde27,0x4331,0xc030,
0x9259,0xda77,0x9007,0x4033,
0xafd5,0x06ce,0x656c,0xc020,
};
static short Q[20] = {
0x0eab,0x0b5e,0x7b59,0xc02d,
0x9054,0x25fe,0x9fc0,0x4051,
0x76d7,0x6d35,0x65bb,0xc062,
0xbf9d,0x84ff,0x7056,0x4061,
0x07ac,0x0a36,0x9822,0xc048,
};
static short R[20] = {
0x9f08,0x988e,0x4fc3,0x3f68,
0x290f,0x59f9,0x0792,0xbfe2,
0x3e6a,0xbaf3,0xdff5,0x401b,
0xab68,0xac01,0x91aa,0xc039,
0x081d,0x40f3,0x8962,0x403c,
};
static short S[16] = {
/* 0x0000,0x0000,0x0000,0x3ff0, */
0x5d8c,0xb6bf,0xf2a2,0xc035,
0x7f42,0xaf6a,0x6219,0x4062,
0x63ee,0x9590,0xfe08,0xc077,
0x44be,0xb0b6,0x6709,0x4075,
};

#define MOREBITS 6.123233995736765886130E-17

double PIO2 = M_PI/2;
double PIO4 = M_PI/4;

int merror = 0;

static char *ermsg[7] = {"unknown",
                         "domain",
                         "singularity",
                         "overflow",
                         "underflow",
                         "total loss of precision",
                         "partial loss of precision"};

void mtherr( char *name, int code )
{
  printf( "\n%s ", name );
  merror = code;
  if( (code <= 0) || (code >= 6) )
    code = 0;
  printf( "%s error\n", ermsg[code] );
}

double polevl(double x, double coef[], int N )
{
  double ans;
  int i;
  double *p;

  p = coef;
  ans = *p++;
  i = N;

  do {
 	  ans = ans * x  +  *p++;
  } while( --i );

  return( ans );
}

double p1evl(double x, double coef[], int N )
{
  double ans;
  double *p;
  int i;

  p = coef;
  ans = x + *p++;
  i = N-1;

  do {
	  ans = ans * x  + *p++;
  } while( --i );

  return( ans );
}

double acos(double x)
{
  double z;

  if( (x < -1.0) || (x > 1.0) )
	{
	  mtherr( "acos", DOMAIN );
  	return( -1 );
	}
  if( x > 0.5 )
	{
	  return( 2.0 * asin(  sqrt(0.5 - 0.5*x) ) );
	}
  z = PIO4 - asin(x);
  z = z + MOREBITS;
  z = z + PIO4;
  return( z );
}

void main()
{
  double cosval;
  printf("\nNhap mot gia tri cos [-1,1] : ");
  scanf("%lf", &cosval);
  printf("arccos(%lf) = %lf", cosval, acos(cosval));
}

