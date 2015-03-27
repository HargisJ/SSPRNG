#ifndef _CONVERSION64
#define _CONVERSION64

#include "Parent.h"
#include <stdint.h>
#include <random>
#include <bitset>
#include <queue>
#include <mutex>
#include "Queue_static.h"
#include <condition_variable>

using namespace std;

namespace SSPRNG
{	

void Int64ToDouble(uint64_t i, double& d);

void Int64ToDoubleDivide(uint64_t i, double& d);

bool TestInt(uint64_t i);

int BitsRequired(uint64_t i);


/**************************************************************************
* Class for breaking a 64 bit integer into an array of what are 
* essentially 3 bit integers that can be used for values from 0 through 7. 
* Intended specifically for dice rolls.
*
* Uses a function pointer to simply get a 64 bit integer from a PRNG
**************************************************************************/
class dieRoll{
public:
	dieRoll();
	dieRoll(Random64 *);

	~dieRoll();

	void setGenerator(Random64 *);

	unsigned int getNext();

	uint64_t get_current_64();


private:
	uint64_t current_64;

	unsigned int current_Index;

	Random64 * gen;

	unsigned int roll[21];

	void breakUp();
};

class dieRollMulti{
public:
	dieRollMulti();
	dieRollMulti(Random64 *);

	~dieRollMulti();

	void setGenerator(Random64 *);

	unsigned int getNext();



private:
	unsigned int temp;

	Queue<uint64_t> uint64Q;

	Queue<unsigned int> uintQ;

	Random64 * gen;

	unsigned int roll[21];

	void breakUp();

	void Generate64bit();
};

class dieRollMultiV2{
public:
	dieRollMultiV2();
	dieRollMultiV2(Random64 *);

	~dieRollMultiV2();

	void setGenerator(Random64 *);

	unsigned int getNext();

private:
	unsigned int temp;

	Queue<uint64_t> uint64Q;

	Queue<unsigned int> uintQ;

	Random64 * gen;

	//unsigned int roll[21];

	void breakUp();

	void Generate64bit();

	void ThreadFunction(Random64 *);
};

class dieRollMultiV3{
public:
	dieRollMultiV3();
	dieRollMultiV3(Random64 *);

	~dieRollMultiV3();

	void setGenerator(Random64 *);

	unsigned int getNext();

private:
	unsigned int temp;

	Queue<uint64_t> uint64Q;

	Queue<unsigned int> uintQ;

	Random64 * gen;

	static const int ARRAY_SIZE = 10000000;

	static const int NUM_THREADS = 3;

	int * pArray[NUM_THREADS];

	bool mainLock;

	bool firstDone;

	//Condition variable 
	condition_variable notifyGetNext;

	mutex getNextMTX;

	unique_lock<mutex> * getNextUnique;

	mutex mtxArray[NUM_THREADS];

	mutex mtxArrayForUniques[NUM_THREADS];
	unique_lock<mutex> * uniqueLockArray[NUM_THREADS];

	condition_variable * cvarArray[NUM_THREADS];


	int currentThreadArrayIndex;
	int currentValueArrayIndex;

	//unsigned int roll[21];


	void breakUp();

	void Generate64bit();

	void ThreadFunction(Random64 *, unsigned int);
};



class coinFlip{
public:
	coinFlip();
	coinFlip(Random64 *);

	~coinFlip();

	void setGenerator(Random64 *);

	unsigned int getNext();

	uint64_t get_current_64();


private:
	unsigned int current_Index;

	uint64_t current_64;

	Random64 * gen;

	unsigned int flips[64];

	void breakUp();

};

//Class using the C++11 implementation of the Mersenne Twister



}

#endif