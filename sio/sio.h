#ifndef SIO_H
#define SIO_H

#ifndef SIO_DEBUG
#define SIO_DEBUG 0
#endif

#include "io.h"

#define INDEX_PORT 0x2E  //change 4E,4F  if  H/W design
#define DATA_PORT  0x2F

//Unlock: Winbond2E/4E(87,87);ITE2E(87,01,55,55)+ITE4E(87,01,55,AA);Fintek2E/4E(87,87);SMSC2E/4E(0x55);AST SIO 2E/4E(A5,A5)
//Lock	: Winbond2E/4E(AA);ITE(Index02,bit1->1(2))Fintek2E/4E(AA);SMSC2E/4E(0xAA) ;AST SIO 2E/4E(AA)

//Winbond
#define WB_UNLOCK	0x87
#define WB_LOCK		0xAA
//NCT
#define NCT_UNLOCK	0x87
#define NCT_LOCK 	0xAA
//ITE
#define ITE_LOCK		0x02
#define ITE_LOCK_REG	0x02
//Fintek
#define FTEK_UNLOCK	0x87
#define FTEK_LOCK	0xAA
#define FTEK_VIDREG_H	0x23
#define FTEK_VIDREG_L	0x24
#define FTEK_VID		0x1934
//SMSC
#define SMSC_UNLOCK	0x55
#define SMSC_LOCK	0xAA

//AST
#define AST_UNLOCK	0xA5
#define AST_LOCK		0xAA

//SIO_REG
#define LDN_REG		0x07
#define CHIP_REG_H	0x20
#define CHIP_REG_L	0x21
#define ACTIVE_REG	0x30


enum SioVendorId	//if you want register sio you must resiter sioId at 0<sioid<FinalId
{
	UnknowId=-1,//-1
	SmscId,	//00
	IteId,		//01
	FintekId,	//02
	NctId,		//03
	WinbondId,	//04
	AstId,	
	FinalId,
};

typedef  struct SioAndOrStruct
{
	unsigned char ldn;
	unsigned char reg;
	unsigned char and_data; 
	unsigned char or_data; 
	unsigned char data;//record current data
}SioAndOr;

class Csio : public Cio
{
public:
	int unlock_flag; //1:Access  sio register need unlock  ,lock  0: do not need  unlock lock
	unsigned short index_port;
	unsigned short data_port;
public:
	Csio() ;
	~Csio();
	virtual	int unlock(); //return -1 :do nothing, 0:unlocked ,1:fail
	virtual	int lock();//return -1 :do nothing, 0:locked ,1:fail
	virtual	int who();//return SioVendorId.
	unsigned short chipId();
	unsigned char read(unsigned char ldn,unsigned char reg);
	int write(unsigned char ldn,unsigned char reg,unsigned char data);
	int active(unsigned char ldn,unsigned char bit=1);
	int and_or(SioAndOr *p);
	int and_or(SioAndOr *p,int count);
	int modfiy(SioAndOr *dest,SioAndOr *src);
	int modfiy(SioAndOr *dest,int count,SioAndOr *src);
	int modfiy(SioAndOr *dest,unsigned char ldn,unsigned char reg,unsigned char and_data,unsigned char or_data);
	int modfiy(SioAndOr *dest,int count,unsigned char ldn,unsigned char reg,unsigned char and_data,unsigned char or_data);
	int get_data(SioAndOr *dest,unsigned char ldn,unsigned char reg,unsigned char *pdata);
	int get_data(SioAndOr *dest,int count,unsigned char ldn,unsigned char reg,unsigned char *pdata);
	int sync(SioAndOr *dest,int dest_count,SioAndOr *src,int src_count);//src->dest
};

class Cite:public Csio //ITE
{
public:
	int unlock();
	int lock();
	int who();
};

class Cwinbond:public Csio //Winbond
{
public:
	int unlock();
	int lock();
	int who();
};

class Cfintek:public Csio //Fintek
{
public:
	int unlock();
	int lock();
	int who();
};

class Csmsc:public Csio //SMSC
{
public:
	int unlock();
	int lock();
	int who();
};

class Cnct:public Csio //NCT
{
public:
	int unlock();
	int lock();
	int who();
};

class Cast:public Csio //AST
{
public:
	int unlock();
	int lock();
	int who();
};

#endif