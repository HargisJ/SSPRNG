#ifndef _MULTIPLICATIVE
#define _MULTIPLICATIVE

namespace SSPRNG
{

//Class for random number generator using the multiplicative congruential method
struct multRandom
{
	int seed;
	int multiplier;
	int min;
	int max;
	int offset;
	int range;

	multRandom(int, int, int, int);
	~multRandom();

	int nextInt();

	}

}
#endif