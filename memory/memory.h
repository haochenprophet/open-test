#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <iostream>

class Cmemory
{
public:
	Cmemory();
	~Cmemory();
	int list(unsigned long address,unsigned long length);
};

#endif