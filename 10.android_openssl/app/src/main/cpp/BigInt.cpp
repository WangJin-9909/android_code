// BigInt1.cpp: implementation of the CBigInt class.
//
//////////////////////////////////////////////////////////////////////
#include "BigInt.h"
#include <stdlib.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//小素数表
const static int PrimeTable[550]=
{   3,    5,    7,    11,   13,   17,   19,   23,   29,   31,
    37,   41,   43,   47,   53,   59,   61,   67,   71,   73,
    79,   83,   89,   97,   101,  103,  107,  109,  113,  127, 
    131,  137,  139,  149,  151,  157,  163,  167,  173,  179, 
    181,  191,  193,  197,  199,  211,  223,  227,  229,  233, 
    239,  241,  251,  257,  263,  269,  271,  277,  281,  283, 
    293,  307,  311,  313,  317,  331,  337,  347,  349,  353, 
    359,  367,  373,  379,  383,  389,  397,  401,  409,  419, 
    421,  431,  433,  439,  443,  449,  457,  461,  463,  467, 
    479,  487,  491,  499,  503,  509,  521,  523,  541,  547, 
    557,  563,  569,  571,  577,  587,  593,  599,  601,  607, 
    613,  617,  619,  631,  641,  643,  647,  653,  659,  661, 
    673,  677,  683,  691,  701,  709,  719,  727,  733,  739, 
    743,  751,  757,  761,  769,  773,  787,  797,  809,  811, 
    821,  823,  827,  829,  839,  853,  857,  859,  863,  877,
    881,  883,  887,  907,  911,  919,  929,  937,  941,  947, 
    953,  967,  971,  977,  983,  991,  997,  1009, 1013, 1019, 
    1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087,
    1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 
    1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223, 1229, 
    1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291, 1297, 
    1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373, 1381,
    1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453, 
    1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511, 1523,
    1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597, 
    1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657, 1663, 
    1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733, 1741, 
    1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811, 1823, 
    1831, 1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889, 1901, 
    1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987, 1993, 
    1997, 1999, 2003, 2011, 2017, 2027, 2029, 2039, 2053, 2063,
    2069, 2081, 2083, 2087, 2089, 2099, 2111, 2113, 2129, 2131, 
    2137, 2141, 2143, 2153, 2161, 2179, 2203, 2207, 2213, 2221, 
    2237, 2239, 2243, 2251, 2267, 2269, 2273, 2281, 2287, 2293,
    2297, 2309, 2311, 2333, 2339, 2341, 2347, 2351, 2357, 2371,
    2377, 2381, 2383, 2389, 2393, 2399, 2411, 2417, 2423, 2437, 
    2441, 2447, 2459, 2467, 2473, 2477, 2503, 2521, 2531, 2539, 
    2543, 2549, 2551, 2557, 2579, 2591, 2593, 2609, 2617, 2621, 
    2633, 2647, 2657, 2659, 2663, 2671, 2677, 2683, 2687, 2689, 
    2693, 2699, 2707, 2711, 2713, 2719, 2729, 2731, 2741, 2749, 
    2753, 2767, 2777, 2789, 2791, 2797, 2801, 2803, 2819, 2833, 
    2837, 2843, 2851, 2857, 2861, 2879, 2887, 2897, 2903, 2909,
    2917, 2927, 2939, 2953, 2957, 2963, 2969, 2971, 2999, 3001,
    3011, 3019, 3023, 3037, 3041, 3049, 3061, 3067, 3079, 3083,
    3089, 3109, 3119, 3121, 3137, 3163, 3167, 3169, 3181, 3187, 
    3191, 3203, 3209, 3217, 3221, 3229, 3251, 3253, 3257, 3259, 
    3271, 3299, 3301, 3307, 3313, 3319, 3323, 3329, 3331, 3343,
    3347, 3359, 3361, 3371, 3373, 3389, 3391, 3407, 3413, 3433, 
    3449, 3457, 3461, 3463, 3467, 3469, 3491, 3499, 3511, 3517, 
    3527, 3529, 3533, 3539, 3541, 3547, 3557, 3559, 3571, 3581,
    3583, 3593, 3607, 3613, 3617, 3623, 3631, 3637, 3643, 3659, 
    3671, 3673, 3677, 3691, 3697, 3701, 3709, 3719, 3727, 3733, 
    3739, 3761, 3767, 3769, 3779, 3793, 3797, 3803, 3821, 3823, 
    3833, 3847, 3851, 3853, 3863, 3877, 3881, 3889, 3907, 3911, 
    3917, 3919, 3923, 3929, 3931, 3943, 3947, 3967, 3989, 4001
};

CBigInt::CBigInt()
{
	m_nLength = 1;
	for( int i = 0 ; i < MAXLEN ; i++ )
	{
		m_nValue[ i ] = 0 ;
	}
}

CBigInt::CBigInt( PBYTE pbyBuffer , DWORD dwBufferSize )
{
	for(int i=0;i<MAXLEN;i++)
	{
		m_nValue[i] = 0;
	}

	UINT nIndex = 0 ;
	while( nIndex < dwBufferSize / 4 )
	{
		memcpy( &m_nValue[ nIndex ] , pbyBuffer + nIndex * 4 , 4 ) ;

		nIndex ++ ;
	}
	
	m_nLength = nIndex ;
}

CBigInt::CBigInt( DWORD dwBufferSize , PBYTE pbyBuffer )
{
	for(int i = 0 ; i < MAXLEN ; i++ )
	{
		m_nValue[i] = 0;
	}
	  
	unsigned long ul = 0 ;

	int nIndex = dwBufferSize /4 ;
	
	m_nLength = nIndex ;

	while( nIndex >=0  )
	{
		memcpy( &m_nValue[ nIndex ] , pbyBuffer + ul * 4 , 4 ) ;
		nIndex -- ;
		ul ++ ;
	}
}

CBigInt::~CBigInt()
{

}
//大数赋值运算符重载=
CBigInt CBigInt::operator=(CBigInt Original)
{
	this->m_nLength = Original.m_nLength ;

	for(int i = 0 ; i < MAXLEN ; i++ )
	{
		this->m_nValue[ i ] = Original.m_nValue[ i ] ;
	}

	return *this ;
}

CBigInt CBigInt::operator=(unsigned long Original)
{
	this->m_nLength = 1 ;

	for(int i = 1 ; i <MAXLEN ; i++ )
	{
		this->m_nValue[ i ] = 0 ;
	}

	this->m_nValue[ 0 ] = Original ;
	
	return *this ;
}
//大数比较运算符重载==、!=、>、<
bool CBigInt::operator==(CBigInt Object)
{
	if( this->m_nLength != Object.m_nLength ) 
	{
		return false ; 
	}

	for(UINT i = 0 ; i < Object.m_nLength ; i++ )
	{
		if( this->m_nValue[ i ] != Object.m_nValue[ i ] )
		{
			return false ;
		}
	}

	return true ;
}

bool CBigInt::operator==(unsigned long Object)
{
	if( this->m_nLength != 1 ) 
	{
		return false ;
	}

	if( this->m_nValue[ 0 ] != Object ) 
	{
		return false ; 
	}

	return true ;
}

bool CBigInt::operator!=(CBigInt Object)
{
	if( this->m_nLength != Object.m_nLength ) 
	{
		return true ; 
	}

	for(UINT i = 0 ; i < Object.m_nLength ; i++ )
	{
		if( this->m_nValue[ i ] != Object.m_nValue[ i ] ) 
		{ 
			return true ; 
		}
	}

	return false;	
}

bool CBigInt::operator!=(unsigned long Object)
{
	if( this->m_nLength != 1 ) 
	{
		return true ;
	}

	if( this->m_nValue[ 0 ] != Object ) 
	{ 
		return true ;
	}

	return false;
}

bool CBigInt::operator>(CBigInt Object)
{
	if( this->m_nLength < Object.m_nLength )
	{
		return false ;
	}
	else if( this->m_nLength == Object.m_nLength )
	{
		int nIndex( 0 ) ;

		for(UINT i = 0 ; i < Object.m_nLength ; i++ )
		{
			nIndex = Object.m_nLength - i - 1 ;
			
			if( nIndex >= 0  &&  nIndex < MAXLEN  )
			{
				//UINT uValue = this->m_nValue[ nIndex ] ;

				if( this->m_nValue[ nIndex ] < Object.m_nValue[ nIndex ] )
				{
					return false ; 
				}
				else if( this->m_nValue[ nIndex ] >Object.m_nValue[ nIndex ] )
				{
					return true ; 
				}
			}
		}

		return false ;
	}
	else 
	{
		return true ; 
	}
}

bool CBigInt::operator>(unsigned long Object)
{
	if( this->m_nLength != 1 )
	{
		return false ; 
	}
	else if( this->m_nValue[ 0 ] > Object )
	{
		return true ; 
	}
	else
	{
		return false ; 
	}
}

bool CBigInt::operator<(CBigInt Object)
{
	if( (*this).m_nLength > Object.m_nLength )
	{
		return false;
	}
	else if( (*this).m_nLength == Object.m_nLength )
	{
		UINT nIndex( 0 ) ;

		for(UINT i = 0 ; i < Object.m_nLength ; i++ )
		{
			nIndex = Object.m_nLength - i - 1 ;
			if( nIndex >= 0   &&  nIndex < MAXLEN )
			{
				if( (*this).m_nValue[ nIndex ] > Object.m_nValue[ nIndex ] )
				{
					return false ;
				}
				else if( (*this).m_nValue[ nIndex ] < Object.m_nValue[ nIndex ] )
				{
					return true ;
				}
			}

		}

		return false ;
	}
	else 
	{
		return true ;
	}
}

bool CBigInt::operator<(unsigned long Object)
{
	if( (*this).m_nLength != 1 )
	{
		return false ;
	}
	else if( (*this).m_nValue[ 0 ] < Object )
	{
		return true ;
	}
	else
	{
		return false ;
	}
}

//大数加、减、乘、除、求余运算符重载+、-、*、/、%
CBigInt CBigInt::operator+(CBigInt Addend)
{
	CBigInt Result = *this ;
	unsigned int carry = 0 ;  
	unsigned long long sum = 0 ;

	if( (*this).m_nLength < Addend.m_nLength )
	{
		Result.m_nLength = Addend.m_nLength ;
	}

	for(UINT i = 0 ; i < Result.m_nLength ; i++ )
	{
		sum = Addend.m_nValue[ i ] ;

		sum += Result.m_nValue[ i ] + carry ;

		Result.m_nValue[ i ] = (unsigned long)sum ;

		carry = (unsigned long)( sum >> 32 ) ;
	}

	int nRLen = Result.m_nLength ;
	if( nRLen >=0 && nRLen <= MAXLEN )
	{
		Result.m_nValue[ nRLen ] = carry ;
	}

	Result.m_nLength += carry ;

	return Result ; 

}

CBigInt CBigInt::operator+(unsigned long Addend)
{
	CBigInt Result ;
	unsigned int carry = 0 ;
	unsigned long long sum = 0 ;

	Result.m_nLength = (*this).m_nLength ;
	sum = (*this).m_nValue[ 0 ] ;
	sum += Addend ;
	Result.m_nValue[ 0 ] = (unsigned long)sum ;

	carry = (unsigned long)( sum >> 32 ) ;

	for(UINT i = 1 ;i < Result.m_nLength ; i++ )
	{
		sum = (*this).m_nValue[ i ] ;
		
		sum += carry ;
		
		Result.m_nValue[ i ] = (unsigned long)sum ;
		
		carry = (unsigned long)( sum >> 32 ) ;
	}

	Result.m_nValue[ Result.m_nLength ] = carry ;

	Result.m_nLength += carry ;	

	return Result ;
}

CBigInt CBigInt::operator-(CBigInt Subtrahend)
{
	CBigInt Result ;
	int carry = 0 ;
	unsigned long long num ;

	if( (*this) < Subtrahend  ||  (*this) == Subtrahend )
	{
		Result = 0 ;
		return Result ;
	}

	Result.m_nLength = (*this).m_nLength ;
	
	for(UINT i=0;i<Result.m_nLength;i++)
	{
		if( (*this).m_nValue[ i ] > Subtrahend.m_nValue[ i ]  || 
			( (*this).m_nValue[ i ] == Subtrahend.m_nValue[ i ] && carry == 0 )  ) 
		{
			Result.m_nValue[ i ] = (*this).m_nValue[ i ] - Subtrahend.m_nValue[ i ] - carry ;
			carry = 0 ;
		}
		else
		{
			num = SYSTEM + (*this).m_nValue[ i ] ;

			Result.m_nValue[ i ] = (unsigned long)( num - Subtrahend.m_nValue[ i ] - carry ) ;
			
			carry = 1 ;
		}
	}

	int nRLen = Result.m_nLength - 1 ;
	if( nRLen >= 0 )
	{
		while( Result.m_nValue[ nRLen ]==0 )
		{
			Result.m_nLength-- ;

			if( Result.m_nLength < 0 )
			{
				break ;
			}
			else
			{
				nRLen = Result.m_nLength -1 ;

				if( nRLen < 0 )
				{
					break ;
				}
			}
		}
	}

	return Result;
}

CBigInt CBigInt::operator-(unsigned long Subtrahend)
{
	CBigInt Result ;
	unsigned long long num ;
	if( (*this) < Subtrahend  ||  (*this) == Subtrahend )
	{
		Result = 0 ;
		return Result ;
	}

	Result = *this ;

	if( (*this).m_nValue[ 0 ] > Subtrahend )
	{
		Result.m_nValue[ 0 ] = (*this).m_nValue[ 0 ] - Subtrahend ;
		return Result ;
	}

	num = SYSTEM + (*this).m_nValue[ 0 ] ;
	Result.m_nValue[ 0 ] = (unsigned long)( num - Subtrahend ) ;

	for(UINT i = 1 ; i < Result.m_nLength ; i++ )
	{
		if( (*this).m_nValue[ i ] == 0 )
		{
			Result.m_nValue[ i ] = 0xffffffff ; 
		}
		else
		{
			Result.m_nValue[ i ]-- ;
			break ;
		}
	}

	if( Result.m_nValue[ Result.m_nLength ] == 0 )
	{
		Result.m_nLength -- ;
	}

	return Result ;
}

CBigInt CBigInt::operator*(CBigInt IER)
{
	CBigInt Result ;
	unsigned long carry = 0 ;
	unsigned long long product ;

	Result.m_nLength = (*this).m_nLength + IER.m_nLength ;

	for(UINT i = 0 ; i < IER.m_nLength ; i++ , carry = 0 )
	{
		for(UINT j = 0 ; j < (*this).m_nLength ; j++ )
		{
			product = (*this).m_nValue[ j ] ;
			product = Result.m_nValue[ i + j ]  +  product * IER.m_nValue[ i ]   + carry ;
			carry = (unsigned long)( product >> 32 ) ;
			Result.m_nValue[ i + j ] = (unsigned long)product ;
		}

		Result.m_nValue[ i + (*this).m_nLength ] = carry ;
	}

	//while( Result.m_nValue[ Result.m_nLength - 1 ] == 0 ) 
	//{
	//	Result.m_nLength -- ; 
	//}

	int nRLen = Result.m_nLength - 1 ;
	if( nRLen >= 0 )
	{
		while( Result.m_nValue[ nRLen ]==0 )
		{
			Result.m_nLength-- ;

			if( Result.m_nLength < 0 )
			{

				break ;
			}
			else
			{
				nRLen = Result.m_nLength -1 ;

				if( nRLen < 0 )
				{
					break ;
				}
			}
		}
	}

	return Result;
}

CBigInt CBigInt::operator*(unsigned long IER)
{
	CBigInt Result = *this ;
	unsigned long carry = 0 ;
	unsigned long long product ;

	for(UINT i = 0 ; i < (*this).m_nLength ; i++ )
	{
		product = (*this).m_nValue[ i ] ;
		product = product * IER + carry ;
		carry = (unsigned long)( product >> 32 ) ;
		Result.m_nValue[ i ] = (unsigned long)product ;
	}

	if( carry != 0 )
	{
		Result.m_nLength ++ ;
		Result.m_nValue[ Result.m_nLength - 1 ] = carry ;
	}

	return Result ;
}

CBigInt CBigInt::operator/(CBigInt Divisor)
{
	if( Divisor.m_nLength == 1 ) 
	{
		return (*this) / Divisor.m_nValue[ 0 ] ;
	}

    CBigInt Quotient , Dividend , Temp ;

    unsigned int i( 0 ) , len( 0 ) ;
    
	unsigned long long num( 0 ) , div( 0 ) ;
    
	Dividend = *this ;
	
	int nTmpIndex1( 0 ) , nTmpIndex2( 0 ) ; 

    while( Dividend > Divisor  ||  Dividend == Divisor )
    {       
		div = Dividend.m_nValue[ Dividend.m_nLength - 1 ] ;

		num = Divisor.m_nValue[ Divisor.m_nLength - 1 ] ;

		len = Dividend.m_nLength - Divisor.m_nLength ;

		if(  ( div == num )   &&  ( len == 0 )   )
		{
			Quotient = Quotient + 1 ;
			break ;
		}

		if(  ( div <= num )  &&  ( len != 0 )   )
		{
			len-- ;
			div = ( div << 32 ) + Dividend.m_nValue[ Dividend.m_nLength - 2 ] ;
		}

		div = div / ( num + 1 ) ;
		Temp = (unsigned long)div ;

		if( len != 0 )
		{
			Temp.m_nLength += len ;

			for( i = Temp.m_nLength - 1 ; i >= len ; i-- ) 
			{
				nTmpIndex1 = i , nTmpIndex2 = i - len ;
				
				if(  ( nTmpIndex1 >= 0   &&  nTmpIndex1< MAXLEN ) && 
					 ( nTmpIndex2 >= 0   &&  nTmpIndex2< MAXLEN ) )
				{
					Temp.m_nValue[ nTmpIndex1 ] = Temp.m_nValue[ nTmpIndex2 ] ;
				}
			}

			for( i = 0 ; i < len ; i++ )
			{
				Temp.m_nValue[ i ] = 0 ; 
			}
		}

		Quotient = Quotient + Temp ;
        Dividend = Dividend - Divisor * Temp ;
    }
    return Quotient ;
}

CBigInt CBigInt::operator/(unsigned long Divisor)
{
	CBigInt Quotient ;
	CBigInt Dividend = *this ;
	unsigned long long num ;

	if( (*this).m_nLength == 1 )
	{
		Quotient.m_nValue[ 0 ] = (*this).m_nValue[ 0 ] / Divisor ;
		return Quotient ;
	}

	Quotient.m_nLength = Dividend.m_nLength ;

	if( Dividend.m_nValue[ Dividend.m_nLength - 1 ] > Divisor )
	{
		Quotient.m_nValue[ Quotient.m_nLength - 1 ] = Dividend.m_nValue[ Dividend.m_nLength - 1 ] / Divisor ;
	}
	else
	{
		Quotient.m_nLength -- ; 
	}

	Dividend.m_nValue[ Dividend.m_nLength - 1 ] = Dividend.m_nValue[ Dividend.m_nLength - 1 ] % Divisor ;

	for( int i = Dividend.m_nLength - 1 ; i > 0 ; i-- )
	{
		num = Dividend.m_nValue[ i ] * SYSTEM + Dividend.m_nValue[ i - 1 ] ;
		
		Quotient.m_nValue[ i - 1 ] = (unsigned long)( num / Divisor ) ;

		Dividend.m_nValue[ i - 1 ] = (unsigned long)( num % Divisor ) ;
	}

	return Quotient ;
}

CBigInt CBigInt::operator%(const CBigInt Divisor)
{
	CBigInt Dividend , Temp ;
	unsigned long long div , num ;
    //unsigned long carry = 0 ;
	unsigned i , len ;

    Dividend = *this ;

	int nTmpIndex1(0) , nTmpIndex2(0) ;

    while( Dividend > Divisor  ||  Dividend == Divisor )
    {
		div = Dividend.m_nValue[ Dividend.m_nLength - 1 ] ;
		
		num =Divisor.m_nValue[ Divisor.m_nLength - 1 ] ;
		
		len =Dividend.m_nLength - Divisor.m_nLength ;

		if( ( div == num )  && ( len == 0 ) )
		{
			Dividend = Dividend - Divisor ;
			break ;
		}

		if( ( div <= num )  &&  len ) 
		{
			len -- ;
			div = ( div << 32 ) + Dividend.m_nValue[ Dividend.m_nLength - 2 ] ;
		}

		div = div / ( num + 1 ) ;
		
		Temp = ( unsigned long ) div ;
		
		Temp = Temp * Divisor ;

		if( len )
		{
			Temp.m_nLength += len ;

			for( i = Temp.m_nLength - 1 ; i >= len ; i-- ) 
			{
				nTmpIndex1 = i , nTmpIndex2 = i - len ;
				
				if(  ( nTmpIndex1 >= 0  &&  nTmpIndex1 < MAXLEN )  &&
					 ( nTmpIndex2 >= 0  &&  nTmpIndex2 < MAXLEN) )
				{
					Temp.m_nValue[ nTmpIndex1 ] = Temp.m_nValue[ nTmpIndex2 ] ;
				}
			}

			for( i = 0 ; i < len ; i++ )
			{
				Temp.m_nValue[ i ] = 0 ; 
			}
		}
 
		Dividend = Dividend - Temp ;
    }

    return Dividend ;
}

CBigInt CBigInt::operator%(unsigned long Divisor)
{
	CBigInt Remainder ;

	if( (*this).m_nLength == 1 )
	{
		Remainder.m_nValue[ 0 ] = (*this).m_nValue[ 0 ] % Divisor ;
		return Remainder ;
	}
    unsigned long long Dividend ;
    
	for(int i = m_nLength - 1 ; i >= 0 ; i-- )
    {
		Dividend = (*this).m_nValue[ i ] + Remainder.m_nValue[ 0 ] * SYSTEM ;
       
		Remainder.m_nValue[ 0 ] = (unsigned long)( Dividend % Divisor ) ;
    }

    return Remainder ;
}

CBigInt CBigInt::Power()
{
	CBigInt Result ;
	CBigInt tempA , Sum ;
	unsigned long tempB ;
	CBigInt carry ; 

	Result.m_nLength = (*this).m_nLength * 2 ;
	
	for(UINT i = 0 ; i < (*this).m_nLength ; i++ )
	{
		tempA = (*this).m_nValue[ i ] ;
		Sum = tempA * tempA + Result.m_nValue[ 2 * i ] ;
		Result.m_nValue[ 2 * i ] = Sum.m_nValue[ 0 ] ;
		carry = Sum.m_nValue[ 1 ] ;
		for(UINT j = i + 1 ; j < (*this).m_nLength ; j++ )
		{
			tempA = (*this).m_nValue[ j ] ;
			tempB = (*this).m_nValue[ i ] ;

			Sum = tempA * tempB * 2 + Result.m_nValue[ i + j ] + carry ;
			
			Result.m_nValue[ i + j ] = Sum.m_nValue[ 0 ] ;
			
			carry = Sum.m_nValue[ 1 ] ;
			
			if( Sum.m_nLength == 3 )
			{
				carry.m_nLength ++ ;
				carry.m_nValue[ 1 ] = Sum.m_nValue[ 2 ] ;
			}
		}

		Result.m_nValue[ i + (*this).m_nLength ] += Sum.m_nValue[ 1 ] ;
		
		if( Sum.m_nLength == 3 )
		{
			Result.m_nValue[ i + (*this).m_nLength + 1 ] = Sum.m_nValue[ 2 ] ;
		}
	}

	if( Result.m_nValue[ Result.m_nLength - 1 ] == 0 )
	{
		Result.m_nLength -- ;
	}

	return Result ;
}

CBigInt CBigInt::PowerMod(CBigInt Degree,CBigInt Modulus)
{
	CBigInt Result ;
	CBigInt Index = Degree ;
	CBigInt Temp ;

	//计算指数的位长len
	int len = ( Index.m_nLength - 1 ) * 32 ;

	unsigned long TopIndex = Index.m_nValue[ Index.m_nLength - 1 ] ;

	while( TopIndex != 0 )
	{
		TopIndex >>= 1 ;
		len ++ ;
	}

	Result = *this ;
	Temp = Result ;
	for( int i = len - 2 ; i >= 0 ; i-- )
	{
		Result = ( Temp * Temp.m_nValue[ Temp.m_nLength - 1 ] ) % Modulus ;
		for(int j = Temp.m_nLength - 1 ; j > 0 ; j-- )
		{
			for(int k = Result.m_nLength ; k > 0 ; k-- )
			{
				Result.m_nValue[ k ] = Result.m_nValue[ k - 1 ] ;
			}

			Result.m_nLength ++ ;
			Result.m_nValue[ 0 ] = 0; 
			Result = ( Result + Temp * Temp.m_nValue[ j - 1 ] ) % Modulus ;
		}
		Temp = Result ;
		if(  ( (Index.m_nValue[ i / 32 ] >> ( i % 32 ) )  & 1 ) == 1 )
		{
			Result = ( Temp * (*this).m_nValue[ (*this).m_nLength - 1 ] ) % Modulus ;
			
			for(int j = (*this).m_nLength - 1 ; j > 0 ; j-- )
			{
				for(int k = Result.m_nLength ; k > 0 ; k-- ) 
				{
					Result.m_nValue[ k ] = Result.m_nValue[ k - 1 ] ;
				}

				Result.m_nLength ++ ;
				Result.m_nValue[ 0 ] = 0 ; 
				Result = ( Result + Temp * (*this).m_nValue[ j - 1 ] ) % Modulus ;
			}
			Temp = Result ;
		}
	}
    return Result ;
}
//求逆
CBigInt CBigInt::Reversion(CBigInt N)
{
	CBigInt M , E , X , Y , I , J ;
    int x , y ;
	M = N ;
	E = *this ;
	X = 0 ;
	Y = 1 ;
	x = y = 1 ;

	while( (E.m_nLength != 1 )   ||  ( E.m_nValue[ 0 ] != 0 )  )
	{
		I = M / E ;
		J = M % E ;
		M = E ;
		E = J ;
		J = Y ;
		Y = Y * I ;
		if( x == y )
		{
		    if( X > Y   ||   X == Y ) 
			{
				Y = X - Y ;
			}
			else
			{
				Y = Y - X ;
				y = 0 ;
			}
		}
		else
		{
			Y = X + Y ;
			x = 1 - x ;
			y = 1 - y ;
		} 

		X = J ;
	}
	if( x == 0 ) 
	{
		X = N - X ;
	}

	return X ;
}

/*************************************************************
采用拉宾米勒得到素数
（1）计算奇数M，使得N=(2**r)*M+1
（2）选择随机数A<N
（3）对于任意i<r，若A**((2**i)*M) MOD N = N-1，则N通过随机数A的测试
（4）或者，若A**M MOD N = 1，则N通过随机数A的测试
（5）让A取不同的值对N进行5次测试，若全部通过则判定N为素数
*************************************************************/
CBigInt CBigInt::GetPrime(int len)
{
	//srand((unsigned)time(NULL));
	*this = 0 ;
	unsigned i ;
    m_nLength = len ;

begin :

	for( i = 0 ; i < m_nLength ; i++ )
	{
		(*this).m_nValue[ i ] = rand() * 0x10000 + rand() ;
	}

    m_nValue[ 0 ] = m_nValue[ 0 ] | 1 ;

	for( i = m_nLength - 1 ; i > 0 ; i-- )
	{
		m_nValue[ i ] = m_nValue[ i ] << 1 ;

		if( m_nValue[ i - 1 ] & 0x80000000 ) 
		{
			m_nValue[ i ] ++ ; 
		}
	}

	m_nValue[ 0 ] = m_nValue[ 0 ] << 1 ;
	m_nValue[ 0 ] ++ ;

    for( i = 0 ; i < 550 ; i++ ) 
	{
		if( (*this) % PrimeTable[ i ] == 0 )
		{
			goto begin ; 
		}
	}

	//拉宾米勒素数测试
    CBigInt S , A , I , K ;
    K = *this ;
	K.m_nValue[ 0 ] -- ;
    for( i = 0 ; i < 5 ; i++ )
	{
        A = rand() * rand() ;
	    S = K / 2 ;
	    I = A.PowerMod( S , *this ) ;

	    if( ( ( I.m_nLength != 1 )   ||  ( I.m_nValue[ 0 ] != 1 )  )  && ( I != K ) ) 
		{
			goto begin ; 
		}
	}

	return *this ;
}


void CBigInt::GetBytes( BYTE * pbyBuffer , DWORD dwBufferSize )
{
	UINT nIndex = 0 ;

	while( nIndex < this->m_nLength )
	{
		if( nIndex * 4 < dwBufferSize )
		{
			memcpy( pbyBuffer + nIndex * 4 , (char*)&m_nValue[ nIndex ] , 4 ) ;
			nIndex ++ ;
		}
		else
		{
			break ;
		}
	}

}

void CBigInt::GetBytes( DWORD dwBufferSize , BYTE * pbyBuffer )
{
	int nIndex = 32 ;
	int ul = 0 ;

	while( nIndex >= 0  )
	{
		if( ul * 4 < int( dwBufferSize ) ) 
		{
			memcpy( pbyBuffer + ul * 4 , &m_nValue[ nIndex ] , 4 ) ;
			nIndex -- ;
			ul ++ ;
		}
		else
		{
			break ; 
		}
	}
}