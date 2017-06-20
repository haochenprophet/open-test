#include "ast_gpio.h"

CAstGpio::CAstGpio()
{

}

CAstGpio::~CAstGpio()
{

}

bool CAstGpio::is_exist(int pin)// 
{

}

void CAstGpio::list_gpio()
{

}

int CAstGpio::parse(int pin)
{

}

int CAstGpio::set_native(int pin)
{

}

int CAstGpio::set_gpi(int pin)
{

}

int CAstGpio::set_gpo(int pin,int high_low)//high_low: GPO_LOW ,GPO_HIGH
{

}

#if ast_gpio_TEST
void help()
{
printf("\
[usage]: gpio [option] {p , l , i , o , n ,} \n\
	p: parse  p <gpio_pin> [gpio_base] ie:./gpio p 36 \n\
	l: list   l [gpio_base=default 500]  ie:./gpio l \n\
	i: input  i <gpi_pin> [gpio_base] ie:./gpio i 36 \n\
	o: ouput  o <gpo_pin> <1:high,0:low> [gpio_base] ie:./gpio  o 36 1 \n\
	n: native n <gpio_pin> [gpio_base] ie:./gpio  n 36\n\n") ; 
}

int main(int argc,char *argv[])
{

	if(argc<2)
	{
		help(); return -1;//do nothing
	}

	return 0;
}

#endif