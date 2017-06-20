#include "sio.h"

Csio::Csio()
{
	this->unlock_flag=1;
	this->index_port=INDEX_PORT;
	this->data_port=DATA_PORT;
}

Csio::~Csio()
{
}

int  Csio::unlock()
{
	return -1;//do nothing
}
int Csio:: lock()
{
	return -1;//do nothing
}

int Csio::who()
{
	return UnknowId;
}

unsigned short Csio::chipId()
{
	unsigned short chipid=0;
	unsigned char data;

	if(this->unlock_flag&&this->unlock()) return -1;

	data=this->isa_read(this->index_port,CHIP_REG_H,this->data_port);
	chipid=(unsigned short )data;
	data=this->isa_read(this->index_port,CHIP_REG_L,this->data_port);
	chipid=chipid<<8;
	chipid|=data;

	if(this->unlock_flag) this->lock();
	return chipid;
}

unsigned char Csio::read(unsigned char ldn,unsigned char reg)
{
	unsigned char data=0;

	if(this->unlock_flag&&this->unlock()) return -1;

	if(reg>=0x30) this->isa_write(this->index_port,LDN_REG,this->data_port,ldn);
	data=this->isa_read(this->index_port,reg,this->data_port);

	if(this->unlock_flag) this->lock();
	return data;
}

int Csio::write(unsigned char ldn,unsigned char reg,unsigned char data)
{
	if(this->unlock_flag&&this->unlock()) return -1;

	this->isa_write(this->index_port,LDN_REG,this->data_port,ldn);
	this->isa_write(this->index_port,reg,this->data_port,data);

	if(this->unlock_flag) this->lock();	
	return 0;
}

int Csio::and_or(SioAndOrStruct *p)
{
	if(this->unlock_flag&&this->unlock()) return -1;

	if(p->reg >= 0x30) this->isa_write(this->index_port,LDN_REG,this->data_port,p->ldn);

	p->data=this->isa_read(this->index_port,p->reg,this->data_port);
	p->data&=p->and_data;
	p->data|=p->or_data;
	this->isa_write(this->index_port,p->reg,this->data_port,p->data);

	if(this->unlock_flag) this->lock();
	return 0;
}

int Csio::and_or(SioAndOrStruct *p,int count)
{
	for(int n=0;n<count;n++)
		this->and_or(&p[n]);
	return 0;
}

int Cite::unlock()
{
	this->byte_write(this->index_port,0x87);
	this->byte_write(this->index_port,0x01);
	this->byte_write(this->index_port,0x55);
	if(this->index_port==0x2E) this->byte_write(this->index_port,0x55);//ITE2E(87,01,55,55)
	else if(this->index_port==0x4E) this->byte_write(this->index_port,0xAA);//ITE4E(87,01,55,AA)
	return 0;
}

int Cite::lock()
{
	this->isa_write(this->index_port,ITE_LOCK_REG,this->data_port,ITE_LOCK);
	return 0;
}

int Cite::who()
{
	return IteId;
}

int Cwinbond::unlock()
{
	this->byte_write(this->index_port,WB_UNLOCK);
	this->byte_write(this->index_port,WB_UNLOCK);
	return 0;
}

int Cwinbond::lock()
{
	this->byte_write(this->index_port,WB_LOCK);
	return 0;
}

int Cwinbond::who()
{
	return WinbondId;
}

int Cnct::unlock()
{
	this->byte_write(this->index_port,NCT_UNLOCK);
	this->byte_write(this->index_port,NCT_UNLOCK);
	return 0;
}

int Cnct::lock()
{
	this->byte_write(this->index_port,NCT_LOCK);
	return 0;
}

int Cnct::who()
{
	return NctId;
}

int Cfintek::unlock()
{
	this->byte_write(this->index_port,FTEK_UNLOCK);
	this->byte_write(this->index_port,FTEK_UNLOCK);
	return 0;
}

int Cfintek::lock()
{
	this->byte_write(this->index_port,FTEK_LOCK);
	return 0;
}

int Cfintek::who()
{
	return FintekId;
}

int Csmsc::unlock()
{
	this->byte_write(this->index_port,SMSC_UNLOCK);
	return 0;
}

int Csmsc::lock()
{
	this->byte_write(this->index_port,SMSC_LOCK);
	return 0;
}

int Csmsc::who()
{
	return SmscId;
}

int Cast::unlock()
{
	this->byte_write(this->index_port,AST_UNLOCK);
	this->byte_write(this->index_port,AST_UNLOCK);
	return 0;
}

int Cast::lock()
{
	this->byte_write(this->index_port,AST_LOCK);
	return 0;
}

int Cast::who()
{
	return AstId;
}


#if SIO_DEBUG
int main()
{
	printf("sio.cpp  main()\n");
	Cite  ite;
	Cwinbond  winbond;
	Csmsc  smsc;
	Cfintek  fintek;
	Cnct  nct;
	Cast  ast;
	return 0;
}
#endif