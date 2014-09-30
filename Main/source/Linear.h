#ifndef _LINEAR_PRNG
#define _LINEAR_PRNG

namespace SSPRNG{

//Class for a linear congruential random number generator
struct LinRandom
{
	int seed;
	int addend;
	int min;
	int max;
	int offset;
	int range;

	LinRandom(int, int, int, int);
	~LinRandom();

	int nextInt();
};

} //namespace SSPRNG

#endif
