
#ifndef ErrorWarning_H
#define ErrorWarning_H
#include <stdio.h>
#include <stdlib.h>
//#include "../object/object.h"
#ifndef ERR_WARN_DEBUG 
#define ERR_WARN_DEBUG 0//1
#endif 

#ifndef	ERRORLEVEL_ERROR
#define ERRORLEVEL_ERROR	2
#endif
#ifndef	ERRORLEVEL_WARNING
#define ERRORLEVEL_WARNING	1
#endif

typedef struct{
	int passCount;
	int	errorCount;
	int	warningCount;
	int	noMatchCount,matchCount;
	int	ignoreCount;
}ErrorWarning;

class CErrorWarning//:public Object
{
	ErrorWarning errWarn;
public:
	CErrorWarning(ErrorWarning *pErrorWarning);
	void incError(ErrorWarning *pErrorWarning);
	void incWarning(ErrorWarning *pErrorWarning);
	void incNoMatch(ErrorWarning *pErrorWarning);
	void incMatch(ErrorWarning *pErrorWarning);
	void incIgnore(ErrorWarning *pErrorWarning);
	void incPass(ErrorWarning *pErrorWarning);
	void clearErrorWarning(ErrorWarning *pErrorWarning);
	void clear(ErrorWarning *p);
	void displayErrorWarning(ErrorWarning *pErrorWarning);
	void checkErrorLvevl(unsigned long errorLvevl,ErrorWarning *pErrorWarning);
	int isPass(ErrorWarning *p);
	CErrorWarning();
	void incError(char *str=NULL,int exit=-1);
	void incWarning();
	void incNoMatch();
	void incMatch();
	void incIgnore();
	void incPass();
	long getError();
	long getWarning();
	long getIgnore();
	long getPass();
	long getNoMatch();
	long getMatch();
	void clearErrorWarning();
	void clear();
	void displayErrorWarning();
	void display(char *cp=0);
	void checkErrorLvevl(unsigned long errorLvevl);
	int isPass();
	int isError();
};

#endif