#include <stdio.h>
#include "register.h"

#ifndef REGISTER_TEST
#define REGISTER_TEST 0//1
#endif

Cregister::Cregister()
{

}

Cregister::~Cregister()
{

}

int Cregister::display(CommonRegister * p)
{
	printf("addr=0x%lX(%ld),data=0x%lX(%ld),and_data=0x%lX,or_data=0x%lX,name=%s,fun=%s,desp=%s\n",
		(long)p->addr,(long)p->addr,(long)p->data,(long)p->data,(long)p->and_data,(long)p->or_data,p->name,p->fun,p->desp);
}

int Cregister::execute(CommonRegister * p)
{
	PRT_ERROR
	return -1;
}

int Cregister::execute(CommonRegister * p,int count)
{
#if REGISTER_TEST
	printf("Cregister::execute->\n");
#endif
	for(int n=0;n<count;n++) this->execute(p);
	return 0;
}

int Cmemory_register::execute(CommonRegister * p)
{
#if REGISTER_TEST
	printf("Cmemory_register::execute->\n");
	this->display(p);//test
#endif

	return 0;
}

int Cio_register::execute(CommonRegister * p)
{
#if REGISTER_TEST
	printf("Cio_register::execute->\n");
	this->display(p);//test
#endif

	return 0;
}

int Csio_register::execute(CommonRegister * p)
{
#if REGISTER_TEST
	printf("Csio_register::execute->\n");
	this->display(p);//test
#endif

	return 0;
}

int Cpci_register::execute(CommonRegister * p)
{
#if REGISTER_TEST
	printf("Cpci_register::execute->\n");
	this->display(p);//test
#endif

	return 0;
}

int Ccpu_register::execute(CommonRegister * p)
{
#if REGISTER_TEST
	printf("Ccpu_register::execute->\n");
	this->display(p);//test
#endif

	return 0;
}

int Cx86_register::execute(CommonRegister * p)
{
#if REGISTER_TEST
	printf("Cx86_register::execute->\n");
	this->display(p);//test
#endif

	return 0;
}

int Carm_register::execute(CommonRegister * p)
{

#if REGISTER_TEST
	printf("Carm_register::execute->\n");
	this->display(p);//test
#endif

	return 0;
}

int Cpower_register::execute(CommonRegister * p)
{
#if REGISTER_TEST
	printf("Cpower_register::execute->\n");
	this->display(p);//test
#endif

	return 0;
}

#if REGISTER_TEST

CommonRegister x86_reg[]
{	
	{0x0000+0,0,NO_AND,NO_OR,"x86_name1","x86_fun1","x86_desp1",},
	{0x0004+0,0,NO_AND,NO_OR,"x86_name2","x86_fun2","x86_desp2",},
};

const int x86_reg_count=sizeof(x86_reg)/sizeof(CommonRegister);

CommonRegister memory_reg[]
{	
	{0x0000+0,0,NO_AND,NO_OR,"memory_name2","memory_fun2","memory_desp2",},
	{0x0004+0,0,NO_AND,NO_OR,"memory_name2","memory_fun2","memory_desp2",},
};
const int memory_reg_count=sizeof(memory_reg)/sizeof(CommonRegister);

CommonRegister pci_reg[]
{	
	{0x0000+0,0,NO_AND,NO_OR,"pci_name2","pci_fun2","pci_desp2",},
	{0x0004+0,0,NO_AND,NO_OR,"pci_name2","pci_fun2","pci_desp2",},
};
const int pci_reg_count=sizeof(pci_reg)/sizeof(CommonRegister);

int main(int argc, char *argv[])
{

	Cx86_register cx86;
	Cmemory_register cmem;
	Cpci_register cpci;

	Cregister * p;
	p=(Cregister *)&cx86;
	p->execute(x86_reg,x86_reg_count);

	p=(Cregister *)&cmem;
	p->execute(memory_reg,memory_reg_count);

	p=(Cregister *)&cpci;
	p->execute(pci_reg,pci_reg_count);

	return 0;
}
#endif 