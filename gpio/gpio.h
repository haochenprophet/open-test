#ifndef GPIO_H
#define GPIO_H

#include "io.h"
#include "pin.h"

using std::cout;
using std::endl;

#define OUT_ERROR cout<<"Error:"<<__FILE__<<"/"<<__FUNCTION__<<"/"<<__LINE__<<":"<<endl;

typedef unsigned long GpioAddrT;

#define GPO_LOW  0
#define GPO_HIGH 1

class Cgpio: public Cio
{
public:
	GpioAddrT gpio_base; //memory base ,or io base
public:
	Cgpio();
	void set_gpio_base(GpioAddrT addr);
	virtual bool is_exist(int pin);// this by chipset define ie .some chip gpio 0-32 ,some chip gpio 0-64
	virtual void list_gpio();
	virtual int parse(int pin);
	virtual int set_native(int pin);
	virtual int set_gpi(int pin);
	virtual int set_gpo(int pin,int high_low);//high_low: GPO_LOW ,GPO_HIGH
};

#endif//GPIO_H