#ifndef _SQUARE_PRNG
#define _SQUARE_PRNG

namespace SSPRNG
{

struct SquareRandom
{
	int seed;
	int min;
	int max;
	int offset;
	int range;

	SquareRandom(int, int, int);
	~SquareRandom();

	int nextInt();
};

} //namespace SSPRNG

#endif