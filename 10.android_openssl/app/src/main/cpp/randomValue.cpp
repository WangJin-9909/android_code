#include "randomValue.h"
#include "stdlib.h"
#include "time.h"

randomValue::randomValue( int* source, int nSize )
{
	sourceArray = source;
	size = nSize;

	srand( (unsigned int)time(0) );
}

int randomValue::getRandomValue()
{
	if( sourceArray == NULL )
		return -1;

	int pos = rand()%size;
	int ret = sourceArray[pos];
	while( true )
	{
		if( ret != -1 )
			break;
		
		pos = rand()%size;
		ret = sourceArray[pos];
	}

	sourceArray[pos] = -1;

	return ret;
}

randomValue::~randomValue(void)
{
}
