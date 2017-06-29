
#ifndef  WINDOWS_OS
#define LINUX_OS 1
#endif

#if LINUX_OS
#include <sys/io.h>
#endif

#ifndef IO_DEBUG
#define IO_DEBUG 0
#endif

#include "io.h"
Cio::Cio()
{
#if LINUX_OS
	iopl(3);	//Open Access IO right
#endif
}
Cio::~Cio()
{
#if LINUX_OS
	iopl(0);	//Close Access IO right
#endif
}

unsigned Cio::byte_read(unsigned port)
{
#if LINUX_OS
	return inb(port);
#endif
	return 0;
}

void Cio::byte_write(unsigned char byte,unsigned port)
{
#if LINUX_OS
	 outb(byte,port);
#endif
}

unsigned Cio::word_read(unsigned port)
{
#if LINUX_OS
	return inw(port);
#endif

	return 0;
}

void Cio::word_write(unsigned short word,unsigned port)
{
#if LINUX_OS
	 outw(word,port);
#endif
}

unsigned Cio::dword_read(unsigned port)
{

#if LINUX_OS
	return inl(port);
#endif
	return 0;
}

void Cio::dword_write(unsigned dword,unsigned port)
{
#if LINUX_OS
	 outw(dword,port);
#endif
}

void Cio::list()
{
	unsigned short io_addr=0x00;	
	unsigned char data;

	for(int n=0;n<0xFFFF;n++)
	{
		data=this->byte_read(io_addr+n);
		if(data!=0xFF&&data!=00) printf("io_addr[%04X]=%02X\n",io_addr+n,data);
	}	
}

unsigned  Cio::isa_read(unsigned short index_port,unsigned char index,unsigned short data_port)
{
	this->byte_write(index_port,index);
	return this->byte_read(data_port);
}

void Cio::isa_write(unsigned short index_port,unsigned char index,unsigned short data_port,unsigned char data)
{
	this->byte_write(index_port,index);
	this->byte_write(data_port,data);
}

void Cio::isa_or(unsigned short index_port,unsigned char index,unsigned short data_port,unsigned char bits)
{
	this->byte_write(index_port,index);
	this->byte_write(data_port,(unsigned char)this->byte_read(data_port)|bits);
}

void Cio::isa_and(unsigned short index_port,unsigned char index,unsigned short data_port,unsigned char bits)
{
	this->byte_write(index_port,index);
	this->byte_write(data_port,(unsigned char)this->byte_read(data_port)&bits);
}

#if IO_DEBUG
int main()
{
	printf("io.cpp int main()\n");
	Cio  Cio;
	//Cio.list();
	return 0;
}
#endif