#ifndef PIN_H
#define PIN_H

#include "register.h"

typedef struct CommonPinStruct
{
	const char*  pin_name;
	const char*  fun_name;
	CommonRegister *ctrl; //1-MAX_CTRL_COUNT ctrl bits
	int ctrl_count;
}CommonPin;

class Cpin : public Cregister
{
public:
	Cpin() ;
	~Cpin();
};

#endif