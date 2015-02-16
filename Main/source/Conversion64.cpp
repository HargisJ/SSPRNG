#include <iostream>
#include "Conversion64.h"
#include <cmath>

namespace SSPRNG
{

//Convert a 64 bit integer to a double
void LongLongToDouble(long long int i, double& d)
{
	i = i & 0x3FFFFFFFFFFFFFFF;
	void* vPtr = &i;

	double* dPtr = static_cast<double *>(vPtr);
	d = *dPtr;
}

//Convert a 64 bit integer to a double using division
void LongLongToDoubleDivide(long long int i, double& d)
{
	d = double(i) / (pow(2,64) - 1);
}

//Test an integer to see if its bits will translate to a double between 0 and 1
bool TestInt(long long int i)
{
	if(((i & 0x3FF0000000000000) ^ 0x3FF0000000000000) || i == 0 || i == 0x3FF0000000000000)
	{
		return true;
	}else{
		return false;
	}
}

//Return the number of bits necessary
int BitsRequired(long long int i)
{
	double d = log2 (i);
	return int(d);
}


//Function definitions for dieRoll class
dieRoll::dieRoll(){
	current_Index = 0;
}

dieRoll::dieRoll(unsigned long long int(*function)()){
	current_Index = 0;
	get_64_Int = function;
	current_Long_Long = get_64_Int();
	breakUp();
}

dieRoll::~dieRoll(){

}

void dieRoll::setFunction(unsigned long long int (*function)()){
	get_64_Int = function;
}

unsigned int dieRoll::getNext(){
	if(current_Index < 21){
		current_Index++;
		return roll[current_Index - 1];
	}else{
		current_Long_Long = get_64_Int();
		breakUp();
		current_Index = 0;
		return roll[current_Index];
	}
}

void dieRoll::breakUp(){
	for(int i = 0; i < 21; i++){
		roll[i] = 7 & (current_Long_Long >> (3*i));
		//roll[i] = current_Long_Long;
	}
}

unsigned long long int dieRoll::get_current_Long(){
	return current_Long_Long;
}



} //Namespace SSPRNG