#ifndef REGISTER_H
#define REGISTER_H

#define PRT_ERROR	printf("Error:%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#define PRT_FUN  	printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);

#define UNKNOW_S "Unknow" //string
#define NULL_S (const char*) 0//string

typedef unsigned int  DataType;
typedef unsigned long AddrType;//register Address Type

#define NO_AND (DataType)0xFFFFFFFF
#define NO_OR 0

typedef struct CommonRegisterStruct
{
	AddrType addr;
	DataType data;
	DataType and_data;
	DataType or_data;
	const char*  name;
	const char*  fun;
	const char*  desp;
}CommonRegister;

class Cregister 
{
public:
	Cregister();
	~Cregister();
	virtual int display(CommonRegister * p);	
	virtual int execute(CommonRegister * p);
	int execute(CommonRegister * p,int count);
};

class Cmemory_register:public Cregister
{
public:
	int execute(CommonRegister * p);
};

class Cio_register:public Cregister
{
public:
	int execute(CommonRegister * p);
};

class Csio_register:public Cregister
{
public:
	int execute(CommonRegister * p);
};

class Cpci_register:public Cregister
{
public:
	int execute(CommonRegister * p);
};

class Ccpu_register:public Cregister
{
public:
	int execute(CommonRegister * p);
};

//vendor
class Cx86_register:public Cregister
{
public:
	int execute(CommonRegister * p);
};

class Carm_register:public Cregister
{
public:
	int execute(CommonRegister * p);
};

class Cpower_register:public Cregister
{
public:
	int execute(CommonRegister * p);
};

#endif