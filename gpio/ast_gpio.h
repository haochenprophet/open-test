#ifndef AST_GPIO_H
#define AST_GPIO_H

#include "sio.h"
#include "gpio.h"
#include <string.h>
#include <ctype.h>

#define LPC2AHB_LDN 0x0D
#define AST_GPIO_BASE 0x1E780000
#define MAXIMUM_GPIO 216

#define UNKNOW_S "Unknow" //string
#define NULL_S (const char*) 0//string

typedef unsigned int  DataType;
typedef unsigned long AddrType;//register Address Type

#define NO_AND (DataType)0xFFFFFFFF
#define NO_OR 0

typedef struct CommonRegisterStruct
{
	AddrType addr;
	DataType data;
	DataType and_data;
	DataType or_data;
	const char*  name;
	const char*  fun;
	const char*  desp;
}CommonRegister;

typedef struct AstGpioMapStruct
{
	const char* group_name;//A0-ZZ7
	CommonRegister data; //data register
	CommonRegister direction;
	CommonRegister interrupt_enable;
	CommonRegister interrupt_sensitivity_type0;//interrupt_sensitivity
	CommonRegister interrupt_sensitivity_type1;
	CommonRegister interrupt_sensitivity_type2;
	CommonRegister interrupt_status;	
	CommonRegister reset_tolerant;
	CommonRegister debounce1;
	CommonRegister debounce2;
	CommonRegister cmd_src0;
	CommonRegister cmd_src1;
	CommonRegister input_mask;
}AstGpioMap;

//extern from ast_chips_register.cpp
extern SioAndOr gpio_read_tab[];
extern SioAndOr gpio_write_tab[];
extern AstGpioMap parallel_gpio_map_tab[];
extern AstGpioMap serial_gpio_map_tab[];

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