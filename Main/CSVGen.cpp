#include "source/XORShift.h"
#include <iostream>
#include <stdint.h>
#include <fstream>
#include <random>
#include <chrono>
#include <cmath>

using namespace SSPRNG;
using namespace std;
int main(){
	uint64_t num = 0;

	// typedef std::chrono::high_resolution_clock myclock;
	// myclock::time_point beginning = myclock::now();
	// myclock::duration d = myclock::now();
	

	

	fstream outFile;
	outFile.open("RandomData.csv", fstream::out);

	fstream outFile2; 
	outFile2.open("Twisterdata.csv", fstream::out);

	fstream outFile3;
	outFile3.open("LinearCongruentialData.csv", fstream::out);



	uint64_t x,y;

	x = 0x53927a9e72d8a935;
	y = 0xa836be43c92e1a63;

	//Built in C++11 Mersenne Twister generator
	std::mt19937_64 generator (x);

	// Came from http://nuclear.llnl.gov/CNP/rng/rngman/node4.html
	std::linear_congruential_engine<uint64_t, 2862933555777941757, 3037000493, 0> lin_gen;
	lin_gen.seed(x);
	//std::cout << lin_gen();

	xorshift128_plus * random = new xorshift128_plus(x,y);


	for (int i = 0; i < 1000000; ++i)
	{
		outFile << random->next() << ",";
		outFile2 << generator() << ",";
		
		outFile3 << lin_gen() << ",";
	}

	outFile2.close();
	outFile.close();
	outFile3.close();
}