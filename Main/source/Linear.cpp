#include "Linear.h"

namespace SSPRNG
{

LinRandom::LinRandom(uint64_t iSeed, uint64_t iMultiplier, uint64_t iAddend)
{
	value = iSeed;
	addend = iAddend;
	multiplier = iMultiplier;
}

LinRandom::~LinRandom()
{

}

void LinRandom::Seed(uint64_t x){
	value = x;
}

void LinRandom::setMultiplier(uint64_t x){
	multiplier = x;
}

void LinRandom::setAddend(uint64_t x){
	addend = x;
}

uint64_t LinRandom::next()
{
	value = multiplier*value + addend;
	return value;
}

}