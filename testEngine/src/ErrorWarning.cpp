
#include	"ErrorWarning.h"

#if ERR_WARN_DEBUG
#include <stdio.h>
int main(int argc,char *argv[])
{
	return 0;
}
#endif //ERR_WARN_DEBUG

CErrorWarning::CErrorWarning(ErrorWarning *pErrorWarning)
{
	clearErrorWarning(pErrorWarning);
}

void CErrorWarning::incError(ErrorWarning *pErrorWarning)
{
	pErrorWarning->errorCount++;
}

void CErrorWarning::incNoMatch(ErrorWarning *pErrorWarning)
{
	pErrorWarning->noMatchCount++;
}

void CErrorWarning::incMatch(ErrorWarning *pErrorWarning)
{
	pErrorWarning->matchCount++;
}

void CErrorWarning::incWarning(ErrorWarning *pErrorWarning)
{
	pErrorWarning->warningCount++;
}

void CErrorWarning::incIgnore(ErrorWarning *pErrorWarning)
{
	pErrorWarning->ignoreCount++;
}

void CErrorWarning::incPass(ErrorWarning *pErrorWarning)
{
	pErrorWarning->passCount++;
}

void CErrorWarning::clearErrorWarning(ErrorWarning *pErrorWarning)
{
	pErrorWarning->passCount=0;
	pErrorWarning->errorCount=0;
	pErrorWarning->warningCount=0;
	pErrorWarning->noMatchCount=0;
	pErrorWarning->matchCount=0;
	pErrorWarning->ignoreCount=0;
}

void CErrorWarning::clear(ErrorWarning *p)
{
	clearErrorWarning(p);
}

void  CErrorWarning::checkErrorLvevl(unsigned long errorLvevl,ErrorWarning *pErrorWarning)
{
	if(ERRORLEVEL_ERROR==errorLvevl)
	{	
		printf("Error:");
		incError(pErrorWarning);
	}
	if(ERRORLEVEL_WARNING==errorLvevl)
	{
		printf("Warning:");
		incWarning(pErrorWarning);
	}
}

void CErrorWarning::displayErrorWarning(ErrorWarning *pErrorWarning)
{
	if(pErrorWarning->errorCount>0)
	{printf("Find %d Error .\n",pErrorWarning->errorCount);}

	if(pErrorWarning->warningCount>0)
	{printf("Find %d Warning. \n",pErrorWarning->warningCount);}

	if(pErrorWarning->noMatchCount>0)
	{printf("Find %d noMatch. \n",pErrorWarning->noMatchCount);}

	if(pErrorWarning->matchCount>0)
	{printf("Find %d Match. \n",pErrorWarning->matchCount);}

	if(pErrorWarning->ignoreCount>0)
	{printf("Ignore %d . \n",pErrorWarning->ignoreCount);}

	if(pErrorWarning->passCount>0)
	{printf("Pass %d . \n",pErrorWarning->passCount);}

	if(	pErrorWarning->noMatchCount==0&&
		pErrorWarning->errorCount==0&& 
		pErrorWarning->warningCount==0
		)
	{
		if(pErrorWarning->ignoreCount) printf("All pass except %d ignore\n",pErrorWarning->ignoreCount);
		else printf("All pass.\n") ;
	}
#ifdef	WINDOWS_OS
	_flushall();
#endif
}
int CErrorWarning::isPass(ErrorWarning *p)
{
	if( p->errorCount||
		p->ignoreCount||
		p->matchCount||
		p->noMatchCount||
		p->warningCount
		)
	{
		return 0;
	}
	return 1;
}

CErrorWarning::CErrorWarning()
{
	clearErrorWarning();
}
void CErrorWarning::incError(char *str,int exit)
{
	errWarn.errorCount++;	
	if(str) printf("Error:%s\n",str); //display
	if(exit) this->displayErrorWarning();
#ifdef	WINDOWS_OS
	if(exit) _exit(exit);
#endif	
}

void CErrorWarning::incNoMatch()
{
	errWarn.noMatchCount++;
}

void CErrorWarning::incMatch()
{
	errWarn.matchCount++;
}

void CErrorWarning::incWarning()
{
	errWarn.warningCount++;
}

void CErrorWarning::incIgnore()
{
	errWarn.ignoreCount++;
}

void CErrorWarning::incPass()
{
	errWarn.passCount++;
}

void CErrorWarning::clearErrorWarning()
{
	clearErrorWarning(&errWarn);
}

void CErrorWarning::clear()
{
	clearErrorWarning(&errWarn);
}

long CErrorWarning::getError()
{
	return errWarn.errorCount;
}

long CErrorWarning::getWarning()
{
	return errWarn.warningCount;
}

long CErrorWarning::getNoMatch()
{
	return errWarn.noMatchCount;
}

long CErrorWarning::getMatch()
{
	return errWarn.matchCount;
}

long CErrorWarning::getIgnore()
{
	return errWarn.ignoreCount;
}

long CErrorWarning::getPass()
{
	return errWarn.passCount;
}

void  CErrorWarning::checkErrorLvevl(unsigned long errorLvevl)
{
	checkErrorLvevl(errorLvevl,&errWarn);
}

void CErrorWarning::displayErrorWarning()
{
	displayErrorWarning(&errWarn);
}

void CErrorWarning::display(char *cp)
{
	if(cp) printf("%s",cp);
	displayErrorWarning(&errWarn);
}

int CErrorWarning::isPass()
{
	return isPass(&errWarn);
}

int CErrorWarning::isError()
{
	if(errWarn.errorCount>0) return 1;
	return 0;
}