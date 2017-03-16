#ifndef INTEL_GPIO_H
#define INTEL_GPIO_H

#include "gpio.h"
#include <stdlib.h>

//note: below defien by chipset refine 
#define DEFAULT_GPIO_BASE  0x500  // IO address 0x500,The IO base address should be changed ,or set LPC IO decode to 0x500

//General Purpose I/O Registers  ,  offset 

/*GPIO_USE_SEL :
0 = Signal used as native function.
1 = Signal used as a GPIO.
*/

#define GPIO_USE_SEL  0
#define GPIO_USE_SEL2 0x30
#define GPIO_USE_SEL3 0x40

/*GP_IO_SEL
0 = Output. The corresponding GPIO signal is an output.
1 = Input. The corresponding GPIO signal is an input.
*/

#define GP_IO_SEL  0x4
#define GP_IO_SEL2 0x34
#define GP_IO_SEL3 0x44

//1 = high, 0 = low.
#define GP_LVL  0xC
#define GP_LVL2 0x38
#define GP_LVL3 0x48


class CintelGpio:public Cgpio //intel pch gpio
{
	unsigned int use_sel , io_sel , gp_lvl , bit_n ; //offset for convert
public:
	CintelGpio();
	int convert(int pin); //pin number convert register bit offset 
	bool is_exist(int pin);
	void list_gpio();
	int parse(int pin);
	int set_native(int pin);
	int set_gpi(int pin);
	int set_gpo(int pin,int high_low);
};

#endif //INTEL_GPIO_H