#ifndef PIN_H
#define PIN_H

#include "register.h"

typedef struct PinControlBitsStruct
{
	AddrType addr;
	int bit_n;//bit number 0-64 
	int bit_data;// 0-1
	int operation;//&&,||,! ,==,!=,>,<,>=,<=,
}PinCtrl;

#define MAX_CTRL_COUNT 5
typedef struct CommonPinStruct
{
	const char*  pin_name;
	const char*  fun_name;
	PinCtrl ctrl[MAX_CTRL_COUNT]; //1-MAX_CTRL_COUNT ctrl bits
}CommonPin;


class Cpin : public Cregister
{
public:
	Cpin() ;
	~Cpin();
};


#endif