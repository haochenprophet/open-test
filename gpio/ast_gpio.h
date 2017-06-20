#ifndef AST_GPIO_H
#define AST_GPIO_H

#include "sio.h"
#include "gpio.h"

class CAstGpio: public Cast, public Cgpio
{
public:
	CAstGpio();
	~CAstGpio();

	bool is_exist(int pin);// 
	void list_gpio();
	int parse(int pin);
	int set_native(int pin);
	int set_gpi(int pin);
	int set_gpo(int pin,int high_low);//high_low: GPO_LOW ,GPO_HIGH
};

#endif