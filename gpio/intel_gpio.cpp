
#include "intel_gpio.h"

CintelGpio::CintelGpio()
{
	this->gpio_base=DEFAULT_GPIO_BASE;
}


bool CintelGpio::is_exist(int pin)// this by chipset define ie .some chip gpio 0-32 ,some chip gpio 0-64
{
	if(pin >=0 && pin<96) return true;
	return false;
}

int CintelGpio::convert(int pin)//pin number convert register bit offset 
{
	 //GPIO 0-31
	if(pin>-1&&pin<32)
	{
		this->use_sel=GPIO_USE_SEL;//offset
		this->io_sel=GP_IO_SEL;
		this->gp_lvl=GP_LVL;
		this->bit_n=pin;
		return this->bit_n;
	}
	//GPIO 32-63
	if(pin>31&&pin<64) 
	{
		this->use_sel=GPIO_USE_SEL2;//offset
		this->io_sel=GP_IO_SEL2;
		this->gp_lvl=GP_LVL2;
		this->bit_n=pin-32;
		return this->bit_n;
	}
	//GPIO 64-95 
	if(pin>63&&pin<96)
	{
		this->use_sel=GPIO_USE_SEL3;//offset
		this->io_sel=GP_IO_SEL3;
		this->gp_lvl=GP_LVL3;
		this->bit_n=pin-64;
		return this->bit_n;
	}

	cout<<"pin="<<pin;
	OUT_ERROR

	return -1;//fail not exist the GPIO pin[n] 
}

void CintelGpio::list_gpio()
{
	for(int n=0;n<96;n++) this->parse(n);
}

int CintelGpio::parse(int pin)
{

	if(this->convert(pin)<0) return -1;

	cout<<"GPIO["<<pin<<"]:\t";

	if(this->dword_read(this->gpio_base+this->use_sel)&(1<<this->bit_n) )
	{
		cout<<"GPIO\t";

		if(this->dword_read(this->gpio_base+this->io_sel)&(1<<this->bit_n) )
		{
			cout<<"Input\t";
		}
		else
		{
			cout<<"Ouput\t";
		}

		if(this->dword_read(this->gpio_base+this->gp_lvl)& (1<<this->bit_n))
		{
			cout<<"High\t";
		}
		else
		{
			cout<<"Low\t";
		}

	}
	else
	{
		cout<<"Native\t";
	}

	cout<<"\n";

	return 0;
}

int CintelGpio::set_native(int pin)
{
	if(this->convert(pin)<0) return -1;
	
	this->dword_write( this->dword_read(this->gpio_base+this->use_sel) & ~(1<<this->bit_n) , this->gpio_base+this->use_sel );
	return 0;
}

int CintelGpio::set_gpi(int pin)
{
	if(this->convert(pin)<0) return -1;

	this->dword_write( this->dword_read(this->gpio_base+this->io_sel)|(1<<this->bit_n) , this->gpio_base+this->io_sel );//set input reg
	this->dword_write( this->dword_read(this->gpio_base+this->use_sel)|(1<<this->bit_n) , this->gpio_base+this->use_sel );//set pin as gpio 
	return 0;
}

int CintelGpio::set_gpo(int pin,int high_low)//high_low: GPO_LOW ,GPO_HIGH
{
	if(this->convert(pin)<0) return -1;


	this->dword_write( this->dword_read(this->gpio_base+this->io_sel)& ~(1<<this->bit_n) , this->gpio_base+this->io_sel );//set output reg
	
	if(high_low==GPO_LOW)this->dword_write( this->dword_read(this->gpio_base+this->gp_lvl)& ~(1<<this->bit_n) , this->gpio_base+this->gp_lvl );//set lvl reg
	else this->dword_write( this->dword_read(this->gpio_base+this->gp_lvl)|(1<<this->bit_n) , this->gpio_base+this->gp_lvl );

	this->dword_write( this->dword_read(this->gpio_base+this->use_sel)|(1<<this->bit_n) , this->gpio_base+this->use_sel );//set pin as gpio 

	return 0;
}

#if intel_gpio_TEST

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
	CintelGpio ig;
	GpioAddrT gpio_base=0;
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

		if(argc>3){
			gpio_base=atol(argv[3]);// get gpio base
			ig.set_gpio_base(gpio_base);
		}

		if(argv[1][0]=='p') //parse
		{
			ig.parse(pin); return 0;
		}

		if(argv[1][0]=='i') //set_gpi
		{
			ig.set_gpi(pin); return 0;
		}

		if(argv[1][0]=='n') //set_native
		{
			ig.set_native(pin);	return 0;
		}

	}


	if(argv[1][0]=='l')
	{
		if(argc>2){
			gpio_base=atol(argv[2]);// get gpio base
			ig.set_gpio_base(gpio_base);
		}
		
		ig.list_gpio();

	}

	if(argv[1][0]=='o')
	{
		if(argc<4){ help(); return -1; }

		if(argc>4){
			gpio_base=atol(argv[4]);// get gpio base
			ig.set_gpio_base(gpio_base);
		}


		pin=atol(argv[2]);

		if(argv[3][0]=='1')
		{
			high_low=GPO_HIGH;
		}
		else high_low=GPO_LOW;

		ig.set_gpo(pin,high_low);

	}//

	return 0;
}


#endif