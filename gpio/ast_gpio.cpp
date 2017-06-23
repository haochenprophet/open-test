#include "ast_gpio.h"

CAstGpio::CAstGpio()
{
	this->set_gpio_base(AST_GPIO_BASE);

	this->parallel=parallel_gpio_map_tab;//can change other register tab
	this->serial=serial_gpio_map_tab;

	this->parallel_len=parallel_gpio_map_tab_count;
	this->serial_len=serial_gpio_map_tab_count;
	//printf("parallel_len=%d,serial_len=%d\n",this->parallel_len,this->serial_len);//test ok

	this->parallel_serial=1;//parallel_serial?parallel :serial
	this->map=this->parallel;
	this->map_len=this->parallel_len;
}

CAstGpio::~CAstGpio()
{

}

int CAstGpio::set_map(int parallel_serial)//set register map
{
	this->parallel_serial=parallel_serial;

	if(parallel_serial)
	{
		this->map=this->parallel;//parallel_serial?parallel :serial
		this->map_len=this->parallel_len;
	}
	else
	{
		this->map=this->serial;
		this->map_len=this->serial_len;
	}

	return 0;
}

int CAstGpio::get_number(char * pin_name)//"A0-AB7"
{
	int offset0=0,offset1=0,offset2=0,len;
	
	len=strlen(pin_name);
	
	if(len==3)//"AA0-ZZ7"
	{
		offset2=toupper(pin_name[0])-'A';
		offset1=toupper(pin_name[1])-'A';
		offset0=toupper(pin_name[2])-'0';
		return (offset1*8+(offset2*8+(26*8))+offset0);
	}
	
	if(len==2)//"A0-Z7"
	{
		offset1=toupper(pin_name[0])-'A';
		offset0=toupper(pin_name[1])-'0';
		return (offset1*8+offset0);
	}
	
	return -1;
}

bool CAstGpio::is_exist(int pin)// 
{
	if(pin>=MAXIMUM_GPIO) return false;
	if(pin<0) return false;
	return true;
}

int CAstGpio::gpio_read(AstGpioMap *p)
{
	


	return 0;
}

void CAstGpio::list_gpio()
{
}

int CAstGpio::parse(int pin)
{
	int group=pin/8;
	int bit=pin%8;

	if(group>=this->map_len) return -1;//pin not exist in map tab

	
	return 0;
}

int CAstGpio::parse(char * pin_name)
{


	return 0;
}

int CAstGpio::set_native(int pin)
{
	return 0;
}

int CAstGpio::set_gpi(int pin)
{
	return 0;
}

int CAstGpio::set_gpo(int pin,int high_low)//high_low: GPO_LOW ,GPO_HIGH
{
	return 0;
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