#include "stdafx.h"
#include "CMetaInterface.h"
#include "CInterfaceLoader.h"


void CMetaInterface::ActivateConsole()
{
	gInterface.GameConsole()->Activate();
}

void CMetaInterface::HideConsole()
{
	gInterface.GameConsole()->Hide();
}

void CMetaInterface::ClearConsole()
{
   gInterface.GameConsole()->Clear();
}

bool CMetaInterface::IsConsoleVisible()
{
  return gInterface.GameConsole()->IsConsoleVisible();
}

void CMetaInterface::ConPrintf(const char *format, ...)
{
	char str[3000];
	va_list marker;
	va_start( marker, format );
	int len = vsnprintf_s(str,2999,format,marker);
	va_end( marker );
	str[len]='\0';
	gInterface.GameConsole()->Printf("[MMCL] %s",str);
}

void CMetaInterface::ConDPrintf(const char *format, ...)
{
	char str[3000];
	va_list marker;
	va_start( marker, format );
	int len = vsnprintf_s(str,2999,format,marker);
	va_end( marker );
	str[len]='\0';
	gInterface.GameConsole()->DPrintf("[MMCL-Dev] %s",str);
}

EXPOSE_SINGLE_INTERFACE(CMetaInterface,IMetaInterface,META_INTERFACE_VERSION);