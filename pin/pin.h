#ifndef PIN_H
#define PIN_H

#include "register.h"

// default value define  
#define PIN_NAME (const char*) 0
#define FUN_NAME (const char*) 0
#define CTRL_REG (CommonRegister *) 0
#define CTRL_CNT (int) 0 //ctrl_count

typedef struct CommonPinStruct
{
	const char*  pin_name;
	const char*  fun_name;
	CommonRegister *ctrl; //pin ctrl bits
	int ctrl_count;
}CommonPin;

class Cpin : public Cregister
{
public:
	Cpin() ;
	~Cpin();
};

#endif