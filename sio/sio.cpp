

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

void Csio::write(unsigned char ldn,unsigned char reg,unsigned char data)
{
	if(this->unlock_flag&&this->unlock()) return -1;

	this->isa_write(this->index_port,LDN_REG,this->data_port,ldn);
	this->isa_write(this->index_port,reg,this->data_port,data);

	if(this->unlock_flag) this->lock();	
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
	this->ByteWriteIO(p->index,0x87);
	this->ByteWriteIO(p->index,0x01);
	this->ByteWriteIO(p->index,0x55);
	if(p->index==0x2E) this->ByteWriteIO(p->index,0x55);//ITE2E(87,01,55,55)
	else if(p->index==0x4E) this->ByteWriteIO(p->index,0xAA);//ITE4E(87,01,55,AA)
	return 0;
}

int Cite::lock()
{
	this->IsaIoWrite(p->index,ITE_LOCK_REG,p->data,ITE_LOCK);
	return 0;
}

int Cite::who()
{
	if(chipid==0||chipid==0xFFFF) return 0;
	return 1;
}

int Cwinbond::unlock()
{
	this->ByteWriteIO(p->index,WB_UNLOCK);
	this->ByteWriteIO(p->index,WB_UNLOCK);
	return 0;
}

int Cwinbond::lock()
{
	this->ByteWriteIO(p->index,WB_LOCK);
	return 0;
}

int Cwinbond::who()
{
	if(chipid==0||chipid==0xFFFF) return 0;
	return 1;
}

int Cnct::unlock()
{
	this->ByteWriteIO(p->index,NCT_UNLOCK);
	this->ByteWriteIO(p->index,NCT_UNLOCK);
	return 0;
}

int Cnct::lock()
{
	this->ByteWriteIO(p->index,NCT_LOCK);
	return 0;
}

int Cnct::who()
{
	if(chipid==0||chipid==0xFFFF) return 0;
	if((chipid&0xB350)==0xB350) return 1;
	return 0;
}

int Cfintek::unlock()
{
	this->ByteWriteIO(p->index,FTEK_UNLOCK);
	this->ByteWriteIO(p->index,FTEK_UNLOCK);
	return 0;
}

int Cfintek::lock()
{
	this->ByteWriteIO(p->index,FTEK_LOCK);
	return 0;
}

int Cfintek::who()
{
	unsigned char data;
	if(chipid==0||chipid==0xFFFF) return 0;
 	data=this->IsaIoRead(p->index,FTEK_VIDREG_H,p->data);
	if(data!=0x19) return 0;
	data=this->IsaIoRead(p->index,FTEK_VIDREG_L,p->data);
	if(data!=0x34) return 0;
	return 1;
}

int Csmsc::unlock()
{
	this->ByteWriteIO(p->index,SMSC_UNLOCK);
	return 0;
}

int Csmsc::lock()
{
	this->ByteWriteIO(p->index,SMSC_LOCK);
	return 0;
}

int Csmsc::who()
{
	if(chipid==0||chipid==0xFFFF) return 0;
	return 1;
}


#if SIO_DEBUG
int main()
{
	printf("sio.cpp  main()\n");
	Csio  Csio;
	return 0;
}
#endif