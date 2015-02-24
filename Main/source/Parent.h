#ifndef _PARENT
#define _PARENT 
#include <stdint.h>

namespace SSPRNG{

class Random64{
public: 
	virtual uint64_t next(){}

};

}//namespace SSPRNG

#endif