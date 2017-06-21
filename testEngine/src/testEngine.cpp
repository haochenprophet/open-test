
#include "testEngine.h"

CtestEngine::CtestEngine()
{
	this->count_execute=0;
}

CtestEngine::~CtestEngine()
{
}

int CtestEngine::execute(int errorlevel,char *cmd ,char *desc)
{
	int ret;
	this->count_execute++;
	printf("\n[execute %d test]:\ncmd=%s,desc=%s ,errorlevel=%d\n",this->count_execute,cmd,desc,errorlevel);//test.
	
	if(errorlevel==2)
	{
		this->incIgnore();
		return 0;
	}

	ret=system(cmd);

	if(ret!=0) 
	{
		if(errorlevel==0){
			this->incError();
			printf("Error[%ld]: [execute %d test]:%s\ncmd=%s,errorlevel=%d\n",this->getError(),this->count_execute,desc,cmd,errorlevel);//test.
		}
		if(errorlevel==1)
		{
			this->incWarning();
			printf("Warning[%ld]: [execute %d test]:%s\ncmd=%s,errorlevel=%d\n",this->getWarning(),this->count_execute,desc,cmd,errorlevel);//test.
		}
	}
	else
	{
		this->incPass();
		printf("Pass[%ld]: [execute %d test]:%s\ncmd=%s,errorlevel=%d\n",this->getPass(),this->count_execute,desc,cmd,errorlevel);//test.
	}
	
	return 0;
}

int CtestEngine::execute(char *start,char *end)
{
	int errorlevel=0;
	char * cmd=0;
	char * desc=0;

	for(;(*start=='{'||*start==' '||*start=='\t')&&start<end;start++);
	if(start>=end) return -1;

	if(*start=='1') errorlevel=1;
	if(*start=='2') errorlevel=2;
	
	//printf("*start=%c *(start+1)=%c \n",*start,*(start+1)); //test ok
    
	for(start++;(*start==','||*start==' '||*start=='\t')&&start<end ;start++); //get cmd{ , ,}
	if(start>=end) return -1;

	cmd=start;

	for(;(*start!=',')&&start<end ;start++); //get cmd{ , |,}
	
	if(*start==','||*start=='}') *start=0;
	
	desc=start+1;
	if(desc>=end) desc=0;
	*end=0;

	this->execute(errorlevel,cmd,desc);

	return 0;
}

int CtestEngine::execute(char *filename)
{
	if(this->allotFileMemory(filename)) return -1; //error 
	char *cp,*cp_s,*cp_e; //char start{, } char end
	
	for(cp=this->allot.start;cp<this->allot.end;cp++)
	{
		if(*cp!='{') continue; //get '{'

		cp_s=cp;
		
		for(cp++;cp<this->allot.end;cp++)
		{
			if(*cp=='{')
			{
				printf("Error: %s block {}is not match.\n",filename);
				return -1; //error 
			}
			
			if(*cp!='}') continue ;

			cp_e=cp;
			this->execute(cp_s,cp_e);

			break;
		}

		if(cp>=this->allot.end) break;
	}

	return 0;
}

#if TEST_ENGINE_DEBUG

int main(int argc,char *argv[])
{
	CtestEngine te;

	char default_file[]= "testEngine.ini";
	char * filename=default_file;
	if(argc>1) filename=argv[1];

	te.execute(filename);

	printf("\n[Report] : execute %s result .\n",filename);
	te.displayErrorWarning();

	return (int)te.getError();
}

#endif //TEST_ENGINE_DEBUG