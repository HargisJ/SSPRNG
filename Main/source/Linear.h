#ifndef _LINEAR_PRNG
#define _LINEAR_PRNG

#include "Parent.h"
#include <stdint.h>

namespace SSPRNG{

//Class for a linear congruential random number generator
class LinRandom: public Random64
{
public:
	LinRandom(uint64_t, uint64_t, uint64_t);
	~LinRandom();

	void Seed(uint64_t);

	void setMultiplier(uint64_t);

	void setAddend(uint64_t);

	uint64_t next();

private:
	uint64_t value;

	uint64_t multiplier;

	uint64_t addend;
};

} //namespace SSPRNG

#endif
