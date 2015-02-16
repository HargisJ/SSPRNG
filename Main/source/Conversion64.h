#ifndef _CONVERSION64
#define _CONVERSION64

namespace SSPRNG
{	

void LongLongToDouble(long long int i, double& d);

void LongLongToDoubleDivide(long long int i, double& d);

bool TestInt(long long int i);

int BitsRequired(long long int i);

//
class dieRoll{
public:
	dieRoll();
	dieRoll(unsigned long long int (*)());

	~dieRoll();

	void setFunction(unsigned long long int (*)());

	unsigned int getNext();

	unsigned long long int get_current_Long();

	unsigned int current_Index;


private:
	unsigned long long int (*get_64_Int)();

	unsigned long long int current_Long_Long;

	unsigned int roll[21];

	void breakUp();
};

}

#endif