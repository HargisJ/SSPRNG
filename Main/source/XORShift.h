#ifndef _XORSHIFT
#define _XORSHIFT
#include "Parent.h"
#include <stdint.h>

namespace SSPRNG{

class xorshift128_plus: public Random64 
{
public:
	xorshift128_plus();

	~xorshift128_plus();
	
	xorshift128_plus(uint64_t, uint64_t);

	void setSeed(uint64_t, uint64_t);

	uint64_t next();

private:
	uint64_t state[2];
	uint64_t x, y;

};






}//Namespace SSPRNG


#endif