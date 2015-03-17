#include "MersenneTwister.h"
#include "Parent.h"
#include <stdint.h>
#include <random>

namespace SSPRNG{

//Mersenne Twister class functions
MT_Gen::MT_Gen(uint64_t seed){
	generator = std::mt19937_64(seed);
}

uint64_t MT_Gen::next(){
	return generator();
}

}//Namespace SSPRNG