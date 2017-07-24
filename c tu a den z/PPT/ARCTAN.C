double atan(double x)
{
  double y, z;
  short sign, flag;

#ifdef MINUSZERO
if( x == 0.0 )
	return(x);
#endif
#ifdef INFINITIES
if(x == INFINITY)
	return(PIO2);
if(x == -INFINITY)
	return(-PIO2);
#endif
/* make argument positive and save the sign */
sign = 1;
if( x < 0.0 )
	{
	sign = -1;
	x = -x;
	}
/* range reduction */
flag = 0;
if( x > T3P8 )
	{
	y = PIO2;
	flag = 1;
	x = -( 1.0/x );
	}
else if( x <= 0.66 )
	{
	y = 0.0;
	}
else
	{
	y = PIO4;
	flag = 2;
	x = (x-1.0)/(x+1.0);
	}
z = x * x;
z = z * polevl( z, P, 4 ) / p1evl( z, Q, 5 );
z = x * z + x;
if( flag == 2 )
	z += 0.5 * MOREBITS;
else if( flag == 1 )
	z += MOREBITS;
y = y + z;
if( sign < 0 )
	y = -y;
return(y);
}

/*							atan2	*/

#ifdef ANSIC
double atan2( y, x )
#else
double atan2( x, y )
#endif
double x, y;
{
double z, w;
short code;

code = 0;

#ifdef NANS
if( isnan(x) )
	return(x);
if( isnan(y) )
	return(y);
#endif
#ifdef MINUSZERO
if( y == 0.0 )
	{
	if( signbit(y) )
		{
		if( x > 0.0 )
			z = y;
		else if( x < 0.0 )
			z = -PI;
		else
			{
			if( signbit(x) )
				z = -PI;
			else
				z = y;
			}
		}
	else /* y is +0 */
		{
		if( x == 0.0 )
			{
			if( signbit(x) )
				z = PI;
			else
				z = 0.0;
			}
		else if( x > 0.0 )
			z = 0.0;
		else
			z = PI;
		}
	return z;
	}
if( x == 0.0 )
	{
	if( y > 0.0 )
		z = PIO2;
	else
		z = -PIO2;
	return z;
	}
#endif /* MINUSZERO */
#ifdef INFINITIES
if( x == INFINITY )
	{
	if( y == INFINITY )
		z = 0.25 * PI;
	else if( y == -INFINITY )
		z = -0.25 * PI;
	else if( y < 0.0 )
		z = NEGZERO;
	else
		z = 0.0;
	return z;
	}
if( x == -INFINITY )
	{
	if( y == INFINITY )
		z = 0.75 * PI;
	else if( y <= -INFINITY )
		z = -0.75 * PI;
	else if( y >= 0.0 )
		z = PI;
	else
		z = -PI;
	return z;
	}
if( y == INFINITY )
	return( PIO2 );
if( y == -INFINITY )
	return( -PIO2 );
#endif

if( x < 0.0 )
	code = 2;
if( y < 0.0 )
	code |= 1;

#ifdef INFINITIES
if( x == 0.0 )
#else
if( fabs(x) <= (fabs(y) / MAXNUM) )
#endif
	{
	if( code & 1 )
		{
#if ANSIC
		return( -PIO2 );
#else
		return( 3.0*PIO2 );
#endif
		}
	if( y == 0.0 )
		return( 0.0 );
	return( PIO2 );
	}

if( y == 0.0 )
	{
	if( code & 2 )
		return( PI );
	return( 0.0 );
	}


switch( code )
	{
#if ANSIC
	default:
	case 0:
	case 1: w = 0.0; break;
	case 2: w = PI; break;
	case 3: w = -PI; break;
#else
	default:
	case 0: w = 0.0; break;
	case 1: w = 2.0 * PI; break;
	case 2:
	case 3: w = PI; break;
#endif
	}

z = w + atan( y/x );
#ifdef MINUSZERO
if( z == 0.0 && y < 0 )
	z = NEGZERO;
#endif
return( z );
}
