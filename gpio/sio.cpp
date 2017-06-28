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

int Csio::active(unsigned char ldn,unsigned char bit)
{
	if(this->unlock_flag&&this->unlock()) return -1;

	this->isa_write(this->index_port,LDN_REG,this->data_port,ldn);
	this->isa_or(this->index_port,ACTIVE_REG,this->data_port,bit);

	if(this->unlock_flag) this->lock();
	return 0;
}

int Csio::and_or(SioAndOr *p)
{
	if(this->unlock_flag&&this->unlock()) return -1;

	if(p->reg >= 0x30) this->isa_write(this->index_port,LDN_REG,this->data_port,p->ldn);

	p->data=this->isa_read(this->index_port,p->reg,this->data_port);

	if(!(p->and_data==0xFF&&p->or_data==0x00))//not only read
	{
		p->data&=p->and_data;
		p->data|=p->or_data;
		this->isa_write(this->index_port,p->reg,this->data_port,p->data);
	}

	if(this->unlock_flag) this->lock();
	return 0;
}

int Csio::and_or(SioAndOr *p,int count)
{
	for(int n=0;n<count;n++)
		this->and_or(&p[n]);
	return 0;
}


int Csio::modfiy(SioAndOr *dest,SioAndOr *src)
{
	if(dest->ldn==src->ldn&&dest->reg==src->reg)
	{
		dest->and_data=src->and_data;
		dest->or_data=src->or_data;
		return 0;
	}
	return -1;
}

int Csio::modfiy(SioAndOr *dest,int count,SioAndOr *src)
{
	for(int n=0;n<count;n++)
		this->modfiy(&dest[n],src);
	return 0;	
}

int Csio::modfiy(SioAndOr *dest,unsigned char ldn,unsigned char reg,unsigned char and_data,unsigned char or_data)
{
	if(dest->ldn==ldn&&dest->reg==reg)
	{
		dest->and_data=and_data;
		dest->or_data=or_data;
		return 0;
	}
	return -1;
}

int Csio::modfiy(SioAndOr *dest,int count,unsigned char ldn,unsigned char reg,unsigned char and_data,unsigned char or_data)
{
	for(int n=0;n<count;n++)
		this->modfiy(&dest[n],ldn,reg,and_data,or_data);
	return 0;	
}

int Csio::get_data(SioAndOr *dest,unsigned char ldn,unsigned char reg,unsigned char *pdata)
{
	if(dest->ldn==ldn&&dest->reg==reg)
	{
		*pdata=dest->data;
		return 0;
	}

	return -1; 
}

int Csio::get_data(SioAndOr *dest,int count,unsigned char ldn,unsigned char reg,unsigned char *pdata)
{
	int n;
	for(n=0;n<count;n++)
	{
		if(this->get_data(&dest[n],ldn,reg,pdata)) continue;
		break;
	}

	if(n>=count) return -1;//get fail

	return 0;
}


int Csio::sync(SioAndOr *dest,SioAndOr *src)
{
	if(dest->ldn==src->ldn&&dest->reg==src->reg)
	{
		dest->data=src->data;
		return 0;
	}
	return -1;
}

int Csio::sync(SioAndOr *dest,int dest_count,SioAndOr *src,int src_count,SioAndOr *skip,int skip_count) //dest->data=src->data;
{
	int i,n;
	for(i=0;i<src_count;i++)
	{
		if(skip&&skip_count>0)
		{
			if(this->find(skip,skip_count,src[i].ldn,src[i].reg)) continue;
		}

		for(n=0;n<dest_count;n++)
		{
			this->sync(&dest[n],&src[i]);
		}
	}
}

SioAndOr * Csio::find(SioAndOr *p,int count,unsigned char ldn,unsigned char reg)
{
	int i;
	for(i=0;i<count;i++)
	{
		if(p[i].ldn==ldn&&p[i].reg==reg) return &p[i];
	}

	return (SioAndOr *)0;
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