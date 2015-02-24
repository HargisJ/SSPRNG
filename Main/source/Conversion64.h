#ifndef _CONVERSION64
#define _CONVERSION64

#include "Parent.h"
#include <stdint.h>

namespace SSPRNG
{	

void Int64ToDouble(uint64_t i, double& d);

void Int64ToDoubleDivide(uint64_t i, double& d);

bool TestInt(uint64_t i);

int BitsRequired(uint64_t i);


/*****************************************************************
* Class for breaking a 64 bit integer into an array of what are 
* essentially 3 bit integers that can be used for values from 0 through 7. 
* Intended specifically for dice rolls.
*
* Uses a function pointer to simply get a 64 bit integer from a PRNG
******************************************************************/
class dieRoll{
public:
	dieRoll();
	dieRoll(Random64 *);

	~dieRoll();

	void setGenerator(Random64 *);

	unsigned int getNext();

	uint64_t get_current_64();

	unsigned int current_Index;

private:	
	uint64_t current_64;

	Random64 * gen;

	unsigned int roll[21];

	void breakUp();
};


}

#endif