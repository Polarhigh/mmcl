#ifndef DebugHelp_h__
#define DebugHelp_h__


#define INT_AS_STR(x) #x 
#define _LINE_AS_STR_(x) INT_AS_STR(x) //__LINE__ can only be converted to an actual number by going through this, otherwise the output is literally "__LINE__"
#define __SLINE__ _LINE_AS_STR_(__LINE__) //Gives you the line number in constant string form
#ifdef _DEBUG
	
	#define DbgMsg(pFormat,...) __DbgMsg__(__FILE__":"__FUNCTION__":"__SLINE__":"pFormat,__VA_ARGS__);
#define DbgMsgS(pFormat,...) /##*DbMsgS*##/ __DbgMsg__(pFormat,__VA_ARGS__);
	#define LOG_TRACE TraceLogger traceLogger(__FILE__, __FUNCTION__, __LINE__);

#define FatalError(pFormat,...) {if(IsDebuggerPresent()){__asm{int 3}} \
	__Fatal_Error__("File:"__FILE__ "\nFunction:" __FUNCTION__ "\nLine:" __SLINE__ "\nERROR:" pFormat "\n\nToDo:add some contacts",__VA_ARGS__);}
#else
	#define NODEBUGLOG
	#define DbgMsg(pFormat,...)
	#define DbgMsgS(pFormat,...) 
	#define LOG_TRACE

	#define FatalError(pFormat,...) __Fatal_Error__("File:"__FILE__ "\nFunction:" __FUNCTION__ "\nLine:" __SLINE__ "\nERROR:" pFormat "\n\nToDo:add some contacts",__VA_ARGS__)
#endif


void __DbgMsg__(char const *pFormat, ... );
void __Fatal_Error__(char const *pFormat, ... );
void WriteLog(char *msg);


class TraceLogger 
{
public:
    TraceLogger(const char* fileName, const char* funcName, int lineNumber);
    ~TraceLogger();
    static std::string Indent;
private:
    const char* _fileName;
    const char* _funcName;
	
};

#endif // DebugHelp_h__
