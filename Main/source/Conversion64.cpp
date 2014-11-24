#include <iostream>
#include "Conversion64.h"
#include <cmath>

namespace SSPRNG
{

//Convert a 64 bit integer to a double
void LongLongToDouble(long long int i, double& d)
{
	i = i & 0x3FFFFFFFFFFFFFFF;
	void* vPtr = &i;

	double* dPtr = static_cast<double *>(vPtr);
	d = *dPtr;
}

//Test an integer to see if its bits will translate to a double between 0 and 1
bool TestInt(long long int i)
{
	if((i & 0x3FF0000000000000 && i & 0x000FFFFFFFFFFFFF) || i == 0)
	{
		return true;
	}else{
		return false;
	}
}

//Return the number of bits necessary
int BitsRequired(long long int i)
{
	double d = log2 (i);
	return int(d);
}

}