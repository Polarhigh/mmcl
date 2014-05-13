#include "stdafx.h"
#include "DebugHelp.h"
#include <direct.h>
#include <ctime>


HWND Mhwnd=0;
BOOL CALLBACK EnumWindowsProc(HWND hwnd,LPARAM lParam)
{
	DWORD PID=0;
	GetWindowThreadProcessId(hwnd,&PID);
	if(PID==lParam)
	{
		Mhwnd=hwnd;
		return false;
	}
	return true;
}

void CloseGameWindow()
{
	Mhwnd=0;
	DWORD PID=GetCurrentProcessId();
	EnumWindows(EnumWindowsProc,PID);
	DestroyWindow(Mhwnd);
}

HWND GetGameWindow()
{
	Mhwnd=0;
	DWORD PID=GetCurrentProcessId();
	EnumWindows(EnumWindowsProc,PID);
	return Mhwnd;
}


void __DbgMsg__(char const *pFormat, ... )
{
	
	char str[300];
	va_list marker;
	va_start( marker, pFormat );
	int len = vsnprintf_s(str,299,pFormat,marker);
	va_end( marker );
	str[len]='\0';
	OutputDebugStringA(str);
	 WriteLog(str);


}


void __Fatal_Error__(char const *pFormat, ... )
{

	CloseGameWindow();
	char str[3000];
	va_list marker;
	va_start( marker, pFormat );
	int len = vsnprintf_s(str,2999,pFormat,marker);
	va_end( marker );
	str[len]='\0';
	MessageBoxA(0,str,"Fatal Error",MB_OK);
	if(!IsDebuggerPresent())
		exit(0);
}


 #ifndef NODEBUGLOG
char LogFile[MAX_PATH];
bool LogFileCreated=false;
void CreateLogFile()
{
	if(LogFileCreated)
		return;
	
	if(_mkdir("mmcl")!=0&&errno!=EEXIST)//if direcory was not created, and it's not exists
		return;

	if(_mkdir("mmcl//logs")!=0&&errno!=EEXIST)
		return;
	
	time_t rawtime;
	struct tm * t;
	time ( &rawtime );
	t = localtime ( &rawtime );

	sprintf(LogFile,"mmcl//logs//%i_%i_%i__%i_%i_%i.log",1900+t->tm_year,t->tm_mon,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
  FILE *LFile=fopen(LogFile,"wt");
  if(!LFile)
	  return;
  fprintf(LFile,"LogFileStarted %i/%i/%i  %i:%i:%i\n\n",1900+t->tm_year,t->tm_mon,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
  fclose(LFile);
  LogFileCreated=true;
}
#endif
void WriteLog(char *msg)
{
#ifndef NODEBUGLOG
	if(!LogFileCreated)
		CreateLogFile();
	if(!LogFileCreated)
		return;
	time_t rawtime;
	struct tm * t;

	time ( &rawtime );
	t = localtime ( &rawtime );

	 FILE * LF=fopen(LogFile,"at");
	fprintf(LF,"%i:%i:%i:%s%s",t->tm_hour,t->tm_min,t->tm_sec,TraceLogger::Indent.c_str(),msg);
	fclose(LF);
#endif
}

std::string TraceLogger::Indent;

TraceLogger::TraceLogger(const char* fileName, const char* funcName, int lineNumber) {
    _fileName = fileName;
    _funcName = funcName;
	//__DbgMsg__("%s==>Entering(%s) - (%s:%i)\n",Indent.c_str(),_funcName,_fileName,lineNumber);
	__DbgMsg__("%s==>%s\n",Indent.c_str(),_funcName);
    Indent.append("  ");
}

TraceLogger::~TraceLogger() {
    Indent.resize(Indent.length() - 2);
	//__DbgMsg__("%s<==Leaving(%s) - (%s)\n",Indent.c_str(),_funcName,_fileName);
	  __DbgMsg__("%s<==%s\n",Indent.c_str(),_funcName);	
 //   std::cout << Indent << "Leaving  " << _funcName << "() - (" << _fileName << ")" << std::endl;
}