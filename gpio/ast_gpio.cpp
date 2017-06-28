#include "ast_gpio.h"

CAstGpio::CAstGpio()
{
	this->set_gpio_base(AST_GPIO_BASE);

	this->parallel=parallel_gpio_map_tab;//can change other register tab
	this->serial=serial_gpio_map_tab;

	this->parallel_len=parallel_gpio_map_tab_count;
	this->serial_len=serial_gpio_map_tab_count;
	//printf("parallel_len=%d,serial_len=%d\n",this->parallel_len,this->serial_len);//test ok

	this->parallel_serial=1;//parallel_serial?parallel :serial
	this->map=this->parallel;
	this->map_len=this->parallel_len;
}

CAstGpio::~CAstGpio()
{

}

int CAstGpio::set_map(int parallel_serial)//set register map
{
	this->parallel_serial=parallel_serial;

	if(parallel_serial)
	{
		this->map=this->parallel;//parallel_serial?parallel :serial
		this->map_len=this->parallel_len;
	}
	else
	{
		this->map=this->serial;
		this->map_len=this->serial_len;
	}

	return 0;
}

int CAstGpio::get_number(char * pin_name)//"A0-AB7"
{
	int offset0=0,offset1=0,offset2=0,len;
	if(!pin_name) return -1;

	len=strlen(pin_name);
	
	if(len==3)//"AA0-ZZ7"
	{
		offset2=toupper(pin_name[0])-'A';
		offset1=toupper(pin_name[1])-'A';
		offset0=toupper(pin_name[2])-'0';
		return (offset1*8+(offset2*8+(26*8))+offset0);
	}
	
	if(len==2)//"A0-Z7"
	{
		offset1=toupper(pin_name[0])-'A';
		offset0=toupper(pin_name[1])-'0';
		return (offset1*8+offset0);
	}
	
	return -1;
}

bool CAstGpio::is_exist(int pin)// 
{
	if(pin>=MAXIMUM_GPIO) return false;
	if(pin<0) return false;
	return true;
}


int CAstGpio::gpio_read(CommonRegister *p)
{
	unsigned char data,reg;
	if(!p) return -1;
	if(p->addr>=0xFFFF) return -1; //Unavailable address 

	this->modfiy(ahb_bus_read_tab,ahb_bus_read_tab_count,LPC2AHB_LDN,0xF3,0x00,(unsigned char)(p->addr&0xFC)); //set direction address 
	this->modfiy(ahb_bus_read_tab,ahb_bus_read_tab_count,LPC2AHB_LDN,0xF2,0x00,(unsigned char)(p->addr>>8&0xFF));
	this->modfiy(ahb_bus_read_tab,ahb_bus_read_tab_count,LPC2AHB_LDN,0xF1,0x00,(unsigned char)(AST_GPIO_BASE>>16&0xFF)); //set AST_GPIO_BASE address 
	this->modfiy(ahb_bus_read_tab,ahb_bus_read_tab_count,LPC2AHB_LDN,0xF0,0x00,(unsigned char)(AST_GPIO_BASE>>24&0xFF));

	this->and_or(ahb_bus_read_tab,ahb_bus_read_tab_count);

	reg=0xF7-(unsigned char)(p->addr&0x3);
	if(this->get_data(ahb_bus_read_tab,ahb_bus_read_tab_count,LPC2AHB_LDN,reg,&data)) return -1;
	
	p->data=data;
	return 0;
}

int CAstGpio::gpio_read(AstGpioMap *p)
{
	if(!p) return -1;
	int backup_unlock_flag=this->unlock_flag;
	this->unlock_flag=0;

	this->unlock();

	this->gpio_read(&p->data);
	this->gpio_read(&p->direction);
	this->gpio_read(&p->interrupt_enable);
	this->gpio_read(&p->interrupt_sensitivity_type0);
	this->gpio_read(&p->interrupt_sensitivity_type1);
	this->gpio_read(&p->interrupt_sensitivity_type2);
	this->gpio_read(&p->interrupt_status);
	this->gpio_read(&p->reset_tolerant);
	this->gpio_read(&p->debounce1);
	this->gpio_read(&p->debounce2);
	this->gpio_read(&p->cmd_src0);
	this->gpio_read(&p->cmd_src1);
	this->gpio_read(&p->input_mask);

	this->lock();
	this->unlock_flag=backup_unlock_flag;
	return 0;
}

void CAstGpio::list_gpio()
{
	for(int n=0;n<MAXIMUM_GPIO;n++)
		this->parse(n);
}

int CAstGpio::parse(CommonRegister *p,int bit ,char * s0,char * s1) //bit[x]=0:printf-s0  ,bit[x]=0:printf-s1
{
	if(!p) return -1;
	if(p->addr>=0xFFFF) return -1;//Unavailable address 
	if (p->data&(1<<bit)) printf("%s",s1);
	else  printf("%s",s0);
	return 0;
}

int CAstGpio::parse(AstGpioMap *p,int bit)
{
	if(!p) return -1;
	this->parse(&p->direction,bit,(char *)"Input\t",(char*)"Output\t");	
	this->parse(&p->data,bit,(char *)"Low\t",(char*)"High\t");
	this->parse(&p->interrupt_enable,bit,(char *)"Input\t",(char*)"Output\t");
	this->parse(&p->interrupt_sensitivity_type0,bit,(char *)"interrupt_sensitivity_type0=0\t",(char*)"interrupt_sensitivity_type0=1\t");
	this->parse(&p->interrupt_sensitivity_type1,bit,(char *)"interrupt_sensitivity_type1=0\t",(char*)"interrupt_sensitivity_type1=1\t");
	this->parse(&p->interrupt_sensitivity_type2,bit,(char *)"interrupt_sensitivity_type2=0\t",(char*)"interrupt_sensitivity_type2=1\t");
	this->parse(&p->interrupt_status,bit,(char *)"interrupt_status=0\t",(char*)"interrupt_status=1\t");
	this->parse(&p->reset_tolerant,bit,(char *)"reset_tolerant=0\t",(char*)"reset_tolerant=1\t");
	this->parse(&p->debounce1,bit,(char *)"debounce1=0\t",(char*)"debounce1=1\t");
	this->parse(&p->debounce2,bit,(char *)"debounce2=0\t",(char*)"debounce2=1\t");
	this->parse(&p->cmd_src0,bit,(char *)"cmd_src0=0\t",(char*)"cmd_src0=1\t");
	this->parse(&p->cmd_src1,bit,(char *)"cmd_src1=0\t",(char*)"cmd_src1=1\t");
	this->parse(&p->input_mask,bit,(char *)"input_mask=0\t",(char*)"input_mask=1\t");
	return 0;
}

int CAstGpio::parse(int pin)
{
	int group=pin/8;//in map tab
	int bit=pin%8;

	if(group>=this->map_len) return -1;//pin not exist in map tab

	if(this->gpio_read(&this->map[group])); return -1;

	printf("GPIO%s%d\t",this->map[group].group_name,bit);
	this->parse(&this->map[group],bit);
	printf("\n");//out entry

	return 0;
}

int CAstGpio::parse(char * pin_name)
{
	if(!pin_name) return -1;
	int pin=this->get_number(pin_name);
	if(pin>=0) //0-MAXGPIO
	{
		if(this->parse(pin)) return -1;
	}
	return 0;
}

int CAstGpio::gpio_write(CommonRegister *p)
{
	unsigned char data,reg;
	if(!p) return -1;
	if(p->addr>=0xFFFF) return -1; //Unavailable address 

	data=(unsigned char)p->data; //save data befor read
	if(this->gpio_read(p)) return -1; //get register data to read_tab,and keep other gpio pin setting,

	//sync address data to ahb_bus_write_tab
	this->sync(ahb_bus_write_tab,ahb_bus_write_tab_count,ahb_bus_read_tab,ahb_bus_read_tab_count,skip_sync_tab,skip_sync_tab_count);

	reg=0xF7-(unsigned char)(p->addr&0x3);
	p->data|=data;// set change bits
	this->modfiy(ahb_bus_write_tab,ahb_bus_write_tab_count,LPC2AHB_LDN,reg,0xFF,(unsigned char)p->data);//or_data = p->data
	
	this->and_or(ahb_bus_write_tab,ahb_bus_write_tab_count);//write tab_data to register

	return 0;
}

int CAstGpio::set_native(int pin)
{
	return 0;
}

int CAstGpio::set_gpi(int pin)
{
	return 0;
}

int CAstGpio::set_gpo(int pin,int high_low)//high_low: GPO_LOW ,GPO_HIGH
{
	return 0;
}

#if ast_gpio_TEST
void help()
{
printf("\
[usage]: gpio [option] {p , l , i , o , n ,} \n\
	p: parse  p <gpio_pin> ie:./gpio p 36 \n\
	l: list   l   ie:./gpio l \n\
	i: input  i <gpi_pin>  ie:./gpio i 36 \n\
	o: ouput  o <gpo_pin> <1:high,0:low>  ie:./gpio  o 36 1 \n\
	n: native n <gpio_pin> ie:./gpio  n 36\n\n") ; 
}

int main(int argc,char *argv[])
{
	CAstGpio ast;
	int pin=-1;
	int high_low=-1;

	if(argc<2)
	{
		help(); return -1;//do nothing
	}

	if(argv[1][0]=='p'||argv[1][0]=='i'||argv[1][0]=='n')//p,i,n
	{

		if(argc<3){ help(); return -1;}
		pin=atol(argv[2]);

		if(argv[1][0]=='p') //parse
		{
			ast.parse(pin); return 0;
		}

		if(argv[1][0]=='i') //set_gpi
		{
			ast.set_gpi(pin); return 0;
		}

		if(argv[1][0]=='n') //set_native
		{
			ast.set_native(pin);	return 0;
		}

	}


	if(argv[1][0]=='o')
	{
		if(argc<4){ help(); return -1; }

		pin=atol(argv[2]);

		if(argv[3][0]=='1')
		{
			high_low=GPO_HIGH;
		}
		else high_low=GPO_LOW;

		ast.set_gpo(pin,high_low);

	}//

	return 0;
}

#endif