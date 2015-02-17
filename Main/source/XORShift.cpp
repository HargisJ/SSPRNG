#include "XORShift.h"
#include <stdint.h>

namespace SSPRNG{

xorshift128_plus::xorshift128_plus(){

}

xorshift128_plus::~xorshift128_plus(){

}

xorshift128_plus::xorshift128_plus(uint64_t first, uint64_t second){
	state[0] = first;
	state[1] = second;
}

void xorshift128_plus::setSeed(uint64_t first, uint64_t second){
	state[0] = first;
	state[1] = second;
}

uint64_t xorshift128_plus::next(){
	y = state[0];
	x = state[1];
	state[0] = x;
	y ^= x << 23;
	return ( state[1] = ( y ^ x ^ (y >> 17) ^ (x >> 26))) + x;
}



}//Namespace SSPRNG