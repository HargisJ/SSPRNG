#include "Square.h"
#include <assert.h>

namespace SSPRNG
{

SquareRandom::SquareRandom(int iMin, int iMax, int iSeed)
{
	min = iMin;
	max = iMax;
	assert(min<max);

	seed = iSeed;

	range = max - min + 1;
	offset = 0 - min;
}

int SquareRandom::nextInt()
{
	seed = (seed*seed + offset)%range + min;
	return seed;
}

}