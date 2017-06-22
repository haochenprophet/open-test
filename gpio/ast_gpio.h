#ifndef AST_GPIO_H
#define AST_GPIO_H

#include "sio.h"
#include "gpio.h"
#include <string.h>
#include <ctype.h>

#define LPC2AHB_LDN 0x0D
#define AST_GPIO_BASE 0x1E780000
#define MAXIMUM_GPIO 216

typedef struct AstGpioMapStruct
{
	const char* group_name;//A-Z
	unsigned int data; //data register
	unsigned int direction;
	unsigned int interrupt_enable;
	unsigned int interrupt_sensitivity_type0;//interrupt_sensitivity
	unsigned int interrupt_sensitivity_type1;
	unsigned int interrupt_sensitivity_type2;
	unsigned int interrupt_status;
	unsigned int reset_tolerant;
	unsigned int debouncing;
	unsigned int input_mask;
}AstGpioMap;

class CAstGpio: public Cast, public Cgpio
{
public:
	CAstGpio();
	~CAstGpio();
	int get_number(char * pin_name);//"A0-AB7"
	bool is_exist(int pin);// 
	void list_gpio();
	int parse(int pin);
	int set_native(int pin);
	int set_gpi(int pin);
	int set_gpo(int pin,int high_low);//high_low: GPO_LOW ,GPO_HIGH

};

#endif