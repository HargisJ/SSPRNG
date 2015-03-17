#ifndef _MERSENNETWISTER
#define _MERSENNETWISTER

#include "Parent.h"
#include <stdint.h>
#include <random>

namespace SSPRNG{
	
class MT_Gen: public Random64{
public:
	MT_Gen(uint64_t);
	uint64_t next();
private:
	std::mt19937_64 generator;
};


} //namespace SSPRNG


#endif
