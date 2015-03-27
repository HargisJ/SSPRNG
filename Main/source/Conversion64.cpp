#include <iostream>
#include "Conversion64.h"
#include "Parent.h"
#include <cmath>
#include <stdint.h>
#include <bitset>
#include <thread>
#include <queue>
#include "MersenneTwister.h"


namespace SSPRNG
{

//Convert a 64 bit integer to a double
void Int64ToDouble(uint64_t i, double& d)
{
	i = i & 0x3FFFFFFFFFFFFFFF;
	void* vPtr = &i;

	double* dPtr = static_cast<double *>(vPtr);
	d = *dPtr;
}

//Convert a 64 bit integer to a double using division
void Int64ToDoubleDivide(uint64_t i, double& d)
{
	d = double(i) / 0xFFFFFFFFFFFFFFFE;
}

//Test an integer to see if its bits will translate to a double between 0 and 1
bool TestInt(uint64_t i)
{
	if(((i & 0x3FF0000000000000) ^ 0x3FF0000000000000) || i == 0 || i == 0x3FF0000000000000)
	{
		return true;
	}else{
		return false;
	}
}

//Return the number of bits necessary
int BitsRequired(uint64_t i)
{
	double d = log2 (i);
	return int(d);
}


//Function definitions for dieRoll class
dieRoll::dieRoll(){
	current_Index = 0;
}

dieRoll::dieRoll(Random64 * inGen){
	current_Index = 0;
	gen = inGen;
	current_64 = gen->next();
	breakUp();
}

dieRoll::~dieRoll(){

}

void dieRoll::setGenerator(Random64 * inGen){
	gen = inGen;
}

unsigned int dieRoll::getNext(){
	//Test to see if there is still a roll to get
	if(current_Index < 21){
		//There is a roll
		current_Index++;
		if(roll[current_Index - 1] > 0 && roll[current_Index - 1] < 7){
			return roll[current_Index - 1];
		}else{
			return this->getNext();
		}
	}else{
		//No roll, need new pieces
		current_64 = gen->next();
		breakUp();
		current_Index = 0;
		return this->getNext();
	}
}

//Function to cut up current 64-bit int and store 
//		the pieces in the roll array
void dieRoll::breakUp(){
	for(int i = 0; i < 21; i++){
		roll[i] = 7 & (current_64 >> (3*i));
	}
}

uint64_t dieRoll::get_current_64(){
	return current_64;
}


//Function definitions for dieRollMulti class
dieRollMulti::dieRollMulti(){
}

dieRollMulti::dieRollMulti(Random64 * inGen){
	gen = inGen;

	std::thread (&dieRollMulti::Generate64bit, this).detach();
	std::thread (&dieRollMulti::breakUp, this).detach();

}

dieRollMulti::~dieRollMulti(){

}

void dieRollMulti::setGenerator(Random64 * inGen){
	gen = inGen;
}

unsigned int dieRollMulti::getNext(){
	while(true){
			return uintQ.dequeue();
	}
}

void dieRollMulti::Generate64bit(){
	while(true){
			uint64Q.enqueue(gen->next());
	}
}

void dieRollMulti::breakUp(){
	int i = 0;
	unsigned int x;
	uint64_t current_64;
	while(true){
			current_64 = uint64Q.dequeue();
			for(i = 0; i < 21; i++){
				x = (7 & (current_64 >> (3*i)));
				if (x>0 && x<7){
					uintQ.enqueue(x);
				}
			}
	}
}

//Function definitions for dieRollMultiV2 class
dieRollMultiV2::dieRollMultiV2(){
}

dieRollMultiV2::dieRollMultiV2(Random64 * inGen){
	uint64_t x, y;
	x = 0x53927a9e72d8a935;
	y = 0xa836be43c92e1a63;
	gen = inGen;

	MT_Gen * twister = new MT_Gen(x);
	std::thread (&dieRollMultiV2::ThreadFunction, this, twister).detach();

	// twister = new MT_Gen(y);
	// std::thread (&dieRollMultiV2::ThreadFunction, this, twister).detach();

	// twister = new MT_Gen(y);
	// std::thread (&dieRollMultiV2::ThreadFunction, this, twister).detach();

	// twister = new MT_Gen(y);
	// std::thread (&dieRollMultiV2::ThreadFunction, this, twister).detach();

	// twister = new MT_Gen(y);
	// std::thread (&dieRollMultiV2::ThreadFunction, this, twister).detach();
;

}

dieRollMultiV2::~dieRollMultiV2(){

}

void dieRollMultiV2::setGenerator(Random64 * inGen){
	gen = inGen;
}

unsigned int dieRollMultiV2::getNext(){
		while(uintQ.empty()){
		}
		return uintQ.dequeue();
}

void dieRollMultiV2::breakUp(){
	int i = 0;
	unsigned int x;
	uint64_t current_64;
	while(true){
		if(!uint64Q.empty()){
			current_64 = uint64Q.dequeue();
			for(i = 0; i < 21; i++){
				x = (7 & (current_64 >> (3*i)));
				if (x>0 && x<7){
					uintQ.enqueue(x);
				}
			}
		}
	}
}

void dieRollMultiV2::Generate64bit(){
	while(true){
		//if(uint64Q.size() < 1000000){
			for (int i = 0; i < 3000; ++i)
			{
				uint64Q.enqueue(gen->next());
			}
	}
}

void dieRollMultiV2::ThreadFunction(Random64 * threadGen){
	uint64_t current_64;
	int i;
	unsigned int x;

	while (true){
		current_64 = threadGen->next();

		for(i = 0; i < 21; i++){
			x = (7 & (current_64 >> (3*i)));
			if (x>0 && x<7){
				while(uintQ.isFull()){}//Spinlock
				uintQ.enqueue(x);
			}
		}
	}
}


//Function definitions for dieRollMultiV3 class
dieRollMultiV3::dieRollMultiV3(){
}

dieRollMultiV3::dieRollMultiV3(Random64 * inGen){
	uint64_t x, y;
	x = 0x53927a9e72d8a935;
	y = 0xa836be43c92e1a63;
	gen = inGen;

	mainLock = false;

	firstDone = false;

	currentThreadArrayIndex = 0;
	currentValueArrayIndex = 0;

	MT_Gen * twister;

	getNextUnique = new unique_lock<mutex>(getNextMTX);

	//Initialize arrays, create threads
	for (int i = 0; i < NUM_THREADS; ++i)
	{
		(pArray[i]) = new int[ARRAY_SIZE];

		uniqueLockArray[i] = new unique_lock<mutex>(mtxArrayForUniques[i]);

		cvarArray[i] = new condition_variable();

		twister = new MT_Gen(y);
		std::thread (&dieRollMultiV3::ThreadFunction, this, twister, i).detach();
	}	
	
	//Notify threads
	for (int i = 0; i < NUM_THREADS; ++i)
	{
		cvarArray[i]->notify_one();
	}


;

}

dieRollMultiV3::~dieRollMultiV3(){

}

void dieRollMultiV3::setGenerator(Random64 * inGen){
	gen = inGen;
}

unsigned int dieRollMultiV3::getNext(){
	if(firstDone){
		if(!mainLock){
			for (int i = 0; i < NUM_THREADS; ++i)
			{
				if(mtxArray[i].try_lock()){
					mainLock = true;
					currentValueArrayIndex = 0;
					currentThreadArrayIndex = i;
					return(getNext());
				}	
			}	
			//Otherwise wait, then return by calling function
			notifyGetNext.wait(*getNextUnique);
			return getNext();
		}else{
			if(currentValueArrayIndex < ARRAY_SIZE){
				//cout << "Thread " << currentThreadArrayIndex << ", ";
				return ((pArray[currentThreadArrayIndex])[currentValueArrayIndex++]);
			}else{
				mtxArray[currentThreadArrayIndex].unlock();
				cvarArray[currentThreadArrayIndex]->notify_one();
				mainLock = false;
				return(getNext());
			}
		}
	}else{
		notifyGetNext.wait(*getNextUnique);
		return getNext();
	}
}

void dieRollMultiV3::breakUp(){
	int i = 0;
	unsigned int x;
	uint64_t current_64;
	while(true){
		if(!uint64Q.empty()){
			//qmtx64.lock();
			current_64 = uint64Q.dequeue();
			//qmtx64.unlock();
			for(i = 0; i < 21; i++){
				x = (7 & (current_64 >> (3*i)));
				if (x>0 && x<7){
					//qmtx.lock();
					uintQ.enqueue(x);
					//qmtx.unlock();
				}
				//roll[i] = current_Long_Long;
			}
		}
	}
}

void dieRollMultiV3::Generate64bit(){
	while(true){
		//if(uint64Q.size() < 1000000){
			for (int i = 0; i < 3000; ++i)
			{
				uint64Q.enqueue(gen->next());
			}
	}
}

void dieRollMultiV3::ThreadFunction(Random64 * threadGen, unsigned int ID){
	uint64_t current_64;
	uint64_t x;
	unsigned int current_Index = 0;

	while(true)
	{
		current_Index = 0;
		cvarArray[ID]->wait(*uniqueLockArray[ID]);

		mtxArray[ID].lock();
		while(true)
		{
			if(current_Index >= ARRAY_SIZE)
				break;

			current_64 = threadGen->next();

			for (int i = 0; i < 21; ++i)
			{
				if(current_Index >= ARRAY_SIZE)
					break;

				x = (7 & (current_64 >> (3*i)));

					if (x>0 && x<7){
						//cout << "Thread " << ID << ": " << x << "\n";
						(pArray[ID])[current_Index++] = x;
					}
			}
		}
		mtxArray[ID].unlock();
		firstDone = true;
		notifyGetNext.notify_one();
	}	
}


//Coin flip function defintions
coinFlip::coinFlip(){
	
}

coinFlip::coinFlip(Random64 * generator){
	gen = generator;
	current_64 = generator->next();
	breakUp();
	current_Index = 0;
}

coinFlip::~coinFlip(){

}

void coinFlip::setGenerator(Random64 * generator){
	gen = generator;
}

unsigned int coinFlip::getNext(){
	if(current_Index < 64){
		current_Index++;
		return flips[current_Index - 1];
	}else{
		current_64 = gen->next();
		breakUp();
		current_Index = 1;
		return flips[current_Index - 1];
	}
}

uint64_t coinFlip::get_current_64(){
	return current_64;
}

void coinFlip::breakUp(){
	for(int i = 0; i < 64; i++){
		flips[i] = 1 & (current_64 >> (i));
	}
}




} //Namespace SSPRNG