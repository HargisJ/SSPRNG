#include <iostream>
#include "Conversion64.h"
#include "Parent.h"
#include <cmath>
#include <stdint.h>
#include <bitset>


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
	d = double(i) / (pow(2,64) - 1);
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
	if(current_Index < 21){
		current_Index++;
		if(roll[current_Index - 1] > 0 && roll[current_Index - 1] < 7){
			return roll[current_Index - 1];
		}else{
			return this->getNext();
		}
	}else{
		current_64 = gen->next();
		breakUp();
		current_Index = 0;
		if(roll[current_Index] > 0 && roll[current_Index] < 7){
			return roll[current_Index];
		}else{
			return this->getNext();
		}
	}
}

void dieRoll::breakUp(){
	for(int i = 0; i < 21; i++){
		roll[i] = 7 & (current_64 >> (3*i));
		//roll[i] = current_Long_Long;
	}
}

uint64_t dieRoll::get_current_64(){
	return current_64;
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
	if(current_bitset != NULL)
		delete current_bitset;
}

void coinFlip::setGenerator(Random64 * generator){
	gen = generator;
}

unsigned int coinFlip::getNext(){
	if(current_Index < 64){
		current_Index++;
		return (*current_bitset)[current_Index - 1];
	}else{
		current_64 = gen->next();
		breakUp();
		current_Index = 1;
		return (*current_bitset)[current_Index - 1];
	}
}

uint64_t coinFlip::get_current_64(){
	return current_64;
}

void coinFlip::breakUp(){
	if(current_bitset != NULL)
		delete current_bitset;
	current_bitset = new std::bitset<64> (current_64);
}




} //Namespace SSPRNG