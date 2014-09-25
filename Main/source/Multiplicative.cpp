#include "Multiplicative.h"
#include <assert.h>

namespace SSPRNG
{

multRandom::multRandom(int iMin, int iMax, int iSeed, int iMultiplier)
{
	min = iMin;
	max = iMax;
	assert(min < max);

	seed = iSeed;
	multiplier = iMultiplier;

	range = max - min;
	offset = 0 - min;
}

multRandom::

}