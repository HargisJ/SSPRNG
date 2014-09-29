#ifndef _LINEAR_PRNG
#define _LINEAR_PRNG

namespace SSPRNG{

//Class for a linear congruential random number generator
struct LinRand
{
	int seed;
	int addend;
	int min;
	int max;
	int offset;
	int range;

	int LinRand(int, int, int, int);
	int ~LinRand();

	int nextInt();
}


}
#endif
