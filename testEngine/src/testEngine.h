
#ifndef TEST_ENGINE_H
#define TEST_ENGINE_H

#define TEST_ENGINE_DEBUG 1

#include "AllotMEM.h"
#include "ErrorWarning.h"

class CtestEngine:public CAllotMem,public CErrorWarning 
{
public:
	int count_execute;
public :
	CtestEngine();
	~CtestEngine();
	int execute(int errorlevel,char *cmd ,char *desc);
	int execute(char *start,char *end);
	int execute(char *filename);
};

#endif