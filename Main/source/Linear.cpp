#include "Linear.h"
#include <assert.h>

namespace SSPRNG
{

LinRandom::LinRandom(int iMin, int iMax, int iSeed, int iAddend)
{
	min = iMin;
	max = iMax;
	assert(min < max);

	seed = iSeed;
	addend = iAddend;

	range = max - min + 1;
	offset = 0 - min;
}

LinRandom::~LinRandom()
{

}

int LinRandom::nextInt()
{
	seed = ((seed+offset)+addend)%range + min;
	return seed;
}

}