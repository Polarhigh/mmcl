#ifndef IMetaInterface_h__
#define IMetaInterface_h__
#include <interface.h>
#define META_INTERFACE_VERSION "MetamodClient001"
class IMetaInterface:public IBaseInterface
{
public:
	// activates the console, makes it visible and brings it to the foreground
	virtual void ActivateConsole() = 0;
	virtual void HideConsole() = 0;
	virtual void ClearConsole() = 0;
	virtual bool IsConsoleVisible() = 0;
	virtual void ConPrintf(const char *format, ...) = 0;
	virtual void ConDPrintf(const char *format, ...) = 0;
};

#endif // IMetaInterface_h__
