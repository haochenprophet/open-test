#include <stdio.h>
#include "register.h"

Cregister::Cregister()
{

}

Cregister::~Cregister()
{

}

int Cregister::display(CommonRegister * p)
{
	printf("addr=%lX(%ld),data=%lX(%ld),and_data=0x%lX,or_data=0x%lX,name=%s,fun=%s,desp=%s\n",
		(long)p->addr,(long)p->addr,(long)p->data,(long)p->data,(long)p->and_data,(long)p->or_data,p->name,p->fun,p->desp);
}

int Cregister::execute(CommonRegister * p)
{
	return -1;
}

int Cregister::execute(CommonRegister * p,int count)
{
	for(int n=0;n<count;n++) this->execute(p);
	return 0;
}

int Cmemory_register::execute(CommonRegister * p)
{
	return -1;
}

int Cio_register::execute(CommonRegister * p)
{
	return -1;
}

int Csio_register::execute(CommonRegister * p)
{
	return -1;
}

int Cpci_register::execute(CommonRegister * p)
{
	return -1;
}

int Ccpu_register::execute(CommonRegister * p)
{
	return -1;
}

int Cx86_register::execute(CommonRegister * p)
{
	return -1;
}

int Carm_register::execute(CommonRegister * p)
{
	return -1;
}

int Cpower_register::execute(CommonRegister * p)
{
	return -1;
}

#ifndef REGISTER_TEST
#define REGISTER_TEST 0//1
#endif

#if REGISTER_TEST
int main(int argc, char *argv[])
{

	return 0;
}
#endif 