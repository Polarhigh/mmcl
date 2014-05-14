#ifndef CMetaInterface_h__
#define CMetaInterface_h__
#include <IMetaInterface.h>

class CMetaInterface:public IMetaInterface
{
public:
	void ActivateConsole();
	void HideConsole();
	void ClearConsole();
	bool IsConsoleVisible();
	void ConPrintf(const char *format, ...);
	void ConDPrintf(const char *format, ...);
};

#endif // CMetaInterface_h__
