#ifndef AST_GPIO_H
#define AST_GPIO_H

#include "sio.h"
#include "gpio.h"
#include <string.h>
#include <ctype.h>

#define LPC2AHB_LDN 0x0D
#define AST_GPIO_BASE 0x1E780000
#define MAXIMUM_GPIO 216

#define AST_SCU_BASE 0x1E6E2000

typedef struct AstMultiPinStruct //Multi-function Pins Mapping and Control
{
	CommonPin fun1;
	CommonPin fun2;
	CommonPin Others;
}AstMultiPin;

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
extern SioAndOr ahb_bus_read_tab[];
extern SioAndOr ahb_bus_write_tab[];
extern SioAndOr skip_sync_tab[];
extern AstGpioMap parallel_gpio_map_tab[];
extern AstGpioMap serial_gpio_map_tab[];

extern const int ahb_bus_read_tab_count;
extern const int ahb_bus_write_tab_count;
extern const int skip_sync_tab_count;
extern const int parallel_gpio_map_tab_count;
extern const int serial_gpio_map_tab_count;


class CAstGpio: public Cast, public Cgpio
{
public:
	AstGpioMap * parallel;//parallel_gpio_map_tab[]
	AstGpioMap * serial;//serial_gpio_map_tab[]
	AstGpioMap * map;
	int parallel_serial;//use map table  parallel_serial?parallel :serial
	int parallel_len;//=parallel_gpio_map_tab_count
	int serial_len;	//=serial_gpio_map_tab_count
	int map_len;
public:
	CAstGpio();
	~CAstGpio();
	int set_map(int parallel_serial=1);//parallel_serial?parallel :serial
	int get_number(char * pin_name);//"A0-AB7"
	bool is_exist(int pin);//
	int gpio_read(CommonRegister *p);
	int gpio_read(AstGpioMap *p);
	void list_gpio();
	int parse(CommonRegister *p,int bit ,char * s0,char * s1); //bit[x]=0:printf-s0  ,bit[x]=0:printf-s1
	int parse(AstGpioMap *p,int bit);
	int parse(int pin);
	int parse(char * pin_name);
	int gpio_write(CommonRegister *p);
	int set_native(int pin);
	int set_gpi(int pin);
	int set_gpo(int pin,int high_low);//high_low: GPO_LOW ,GPO_HIGH

};

#endif