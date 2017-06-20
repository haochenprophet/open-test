#include "memory.h"


Cmemory::Cmemory()
{

}

Cmemory::~Cmemory()
{

}

int Cmemory:: list(unsigned long address,unsigned long length)
{

	return length;
}

#if MEMORY_DEBUG
int main()
{
	printf("memory.cpp int main()\n");
	Cmemory  Cmemory;
	Cmemory.list(0xF0000000,0x1000);
	return 0;
}
#endif