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
	p: parse  p <gpio_pin> ie:./gpio p 36 \n\
	l: list   l   ie:./gpio l \n\
	i: input  i <gpi_pin>  ie:./gpio i 36 \n\
	o: ouput  o <gpo_pin> <1:high,0:low>  ie:./gpio  o 36 1 \n\
	n: native n <gpio_pin> ie:./gpio  n 36\n\n") ; 
}

int main(int argc,char *argv[])
{
	CAstGpio ast;
	int pin=-1;
	int high_low=-1;

	if(argc<2)
	{
		help(); return -1;//do nothing
	}

	if(argv[1][0]=='p'||argv[1][0]=='i'||argv[1][0]=='n')//p,i,n
	{

		if(argc<3){ help(); return -1;}
		pin=atol(argv[2]);

		if(argv[1][0]=='p') //parse
		{
			ast.parse(pin); return 0;
		}

		if(argv[1][0]=='i') //set_gpi
		{
			ast.set_gpi(pin); return 0;
		}

		if(argv[1][0]=='n') //set_native
		{
			ast.set_native(pin);	return 0;
		}

	}


	if(argv[1][0]=='o')
	{
		if(argc<4){ help(); return -1; }

		pin=atol(argv[2]);

		if(argv[3][0]=='1')
		{
			high_low=GPO_HIGH;
		}
		else high_low=GPO_LOW;

		ast.set_gpo(pin,high_low);

	}//

	return 0;
}

#endif