#include <iostream>
#include <cstdlib>
#include <chrono>
#include <random>
#include <ctime>
#include "source/Conversion64.h"
#include "source/XORShift.h"
#include "source/Linear.h"
#include <stdint.h>

using namespace std;
using namespace SSPRNG;

int main(int argc, char const *argv[])
{
	//Initialize things
	srand(time(0));

	//xorshift
	uint64_t x, y;
	x = 0x53927a9e72d8a935;
	y = 0xa836be43c92e1a63;

	xorshift128_plus * xor_gen = new xorshift128_plus(x,y);
	dieRoll * die = new dieRoll(xor_gen);

	//Uniform distribution
	default_random_engine generator;
	uniform_int_distribution<int> distribution(1,6);

	//Mersenne twister
	std::mt19937_64 mt_generator (x);

	//Linear congruential
	std::linear_congruential_engine<uint64_t, 2862933555777941757, 3037000493, 0> lin_gen;
	lin_gen.seed(x);

	//My Mersenne Twister Class
	MT_Gen * mt_gen = new MT_Gen(x);
	dieRoll * MT_die = new dieRoll(mt_gen);


	//Timing getting die rolls using traditional std::rand
	cout << "Time using std::rand: ";
	//cout << chrono::high_resolution_clock::period::den << endl;
	auto start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i< 100000000; i++)
		rand() % 6 + 1;
	auto end_time = chrono::high_resolution_clock::now();
	//cout << chrono::duration_cast<chrono::seconds>(end_time - start_time).count() << ":";
	cout << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << " microseconds";
	cout << "\n";

	//Timing getting die rolls using xorshift and my specialized class
	cout << "Time using xorshift and my splitter: ";
	//cout << chrono::high_resolution_clock::period::den << endl;
	start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i< 100000000; i++)
		die->getNext();
	end_time = chrono::high_resolution_clock::now();
	//cout << chrono::duration_cast<chrono::seconds>(end_time - start_time).count() << ":";
	cout << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << " microseconds";
	cout << "\n";

	//Timing getting die rolls using my xorshift
	cout << "Time using xorshift: ";
	//cout << chrono::high_resolution_clock::period::den << endl;
	start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i< 100000000; i++)
		xor_gen->next() % 6 + 1;
	end_time = chrono::high_resolution_clock::now();
	//cout << chrono::duration_cast<chrono::seconds>(end_time - start_time).count() << ":";
	cout << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << " microseconds";
	cout << "\n";

	//Timing using uniform distribution in C++11 random library using default generator
	cout << "Time using default generator and uniform distribution: ";
	//cout << chrono::high_resolution_clock::period::den << endl;
	start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i< 100000000; i++)
		distribution(generator);
	end_time = chrono::high_resolution_clock::now();
	//cout << chrono::duration_cast<chrono::seconds>(end_time - start_time).count() << ":";
	cout << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << " microseconds";
	cout << "\n";

	//Timing using C++11 random library: default generator
	cout << "Time using default generator: ";
	//cout << chrono::high_resolution_clock::period::den << endl;
	start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i< 100000000; i++)
		generator() % 6 + 1;
	end_time = chrono::high_resolution_clock::now();
	//cout << chrono::duration_cast<chrono::seconds>(end_time - start_time).count() << ":";
	cout << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << " microseconds";
	cout << "\n";

	//Timing using mersenne twister in C++11 random library
	cout << "Time using MT generator: ";
	//cout << chrono::high_resolution_clock::period::den << endl;
	start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i< 100000000; i++)
		mt_generator() % 6 + 1;
	end_time = chrono::high_resolution_clock::now();
	//cout << chrono::duration_cast<chrono::seconds>(end_time - start_time).count() << ":";
	cout << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << " microseconds";
	cout << "\n";

	//Timing using mersenne twister and uniform distribution
	cout << "Time using MT generator and uniform distribution: ";
	//cout << chrono::high_resolution_clock::period::den << endl;
	start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i< 100000000; i++)
		distribution(mt_generator);
	end_time = chrono::high_resolution_clock::now();
	//cout << chrono::duration_cast<chrono::seconds>(end_time - start_time).count() << ":";
	cout << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << " microseconds";
	cout << "\n";

	//Timing using linear congruential
	cout << "Time using linear congruential generator C++11: ";
	//cout << chrono::high_resolution_clock::period::den << endl;
	start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i< 100000000; i++)
		lin_gen() % 6 + 1;
	end_time = chrono::high_resolution_clock::now();
	//cout << chrono::duration_cast<chrono::seconds>(end_time - start_time).count() << ":";
	cout << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << " microseconds";
	cout << "\n";

	//Timing using mersenne twister and uniform distribution
	cout << "Time using linear congruential generator and uniform distribution C++11: ";
	//cout << chrono::high_resolution_clock::period::den << endl;
	start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i< 100000000; i++)
		distribution(lin_gen);
	end_time = chrono::high_resolution_clock::now();
	//cout << chrono::duration_cast<chrono::seconds>(end_time - start_time).count() << ":";
	cout << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << " microseconds";
	cout << "\n";

	//Timing getting die rolls using xorshift and my specialized class
	cout << "Time using Mersenne Twister and my splitter: ";
	//cout << chrono::high_resolution_clock::period::den << endl;
	start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i< 100000000; i++)
		MT_die->getNext();
	end_time = chrono::high_resolution_clock::now();
	//cout << chrono::duration_cast<chrono::seconds>(end_time - start_time).count() << ":";
	cout << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << " microseconds";
	cout << "\n";

	//Timing getting die rolls using my xorshift
	cout << "Time using Mersenne Twister: ";
	//cout << chrono::high_resolution_clock::period::den << endl;
	start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i< 100000000; i++)
		mt_gen->next() % 6 + 1;
	end_time = chrono::high_resolution_clock::now();
	//cout << chrono::duration_cast<chrono::seconds>(end_time - start_time).count() << ":";
	cout << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << " microseconds";
	cout << "\n";

	return 0;
}