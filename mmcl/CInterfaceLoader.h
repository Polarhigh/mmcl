#ifndef CInterfaceLoader_h__
#define CInterfaceLoader_h__


/*
#define GET_FACTORY(module_var,module_path)\
	module_var=Sys_LoadModule(module_path);\
	if(!module_var) FatalError("Can't load %s",module_path);\
	CreateInterfaceFn module_var##Factory=Sys_GetFactory(module_var);\
	if(!module_var##Factory) FatalError("Can't get %s factory",module_path);

#define CREATE_AND_VALIDATE_INTERFACE(var,type,factory,name)\
	var = (type)factory##Factory(name, NULL);\
	if(!var)FatalError("Can't create " name " interfase");
*/

#define GET_FACTORY(module_var,module_path)\
	module_var=Sys_LoadModule(module_path);\
	CreateInterfaceFn module_var##Factory;\
	if(module_var)\
	{\
		module_var##Factory=Sys_GetFactory(module_var);\
	}\
	else\
	{\
	   module_var##Factory=Sys_GetFactoryThis();\
	}\

#define CREATE_AND_VALIDATE_INTERFACE(var,type,factory,name)\
	var = (type)factory##Factory(name, NULL);\
	if(!var)var=(type)Sys_GetFactoryThis()(NULL_INTERFACE_VERSION,NULL);

class CInterfaceLoader
{
public:
	CInterfaceLoader();
	~CInterfaceLoader();
	bool Init();
	void ShutDown();
	CreateInterfaceFn FileSystemFactory(){if(!Loaded)Init();return gFileSystemFactory;}
private:
	CreateInterfaceFn gFileSystemFactory;
	CSysModule *mGameUI;
	CSysModule *mEngine;
	CSysModule *mVGUI2;
	CSysModule *mFileSystem;
	bool Loaded;
public:
	IGameUI *GameUI();
	IGameConsole *GameConsole();
	IRunGameEngine *RunGameEngine();
	//hw
	IBaseUI *BaseUI();
	IEngineAPI *EngineAPI();
	//vgui2
	vgui::ILocalize *vgLocalize();
	vgui::ISystem *vgSystem();
	vgui::IInput *vgInput();
	vgui::IInputInternal *vgInputInternal();
	vgui::IPanel *vgPanel();
	vgui::IVGui *vgVGui();
	//FileSystem_Stdio
	IFileSystem *FileSystem();

private:
	IGameUI *iGameUI;
	IGameConsole *iGameConsole;
	IRunGameEngine *iRunGameEngine;
	//hw
	IBaseUI *iBaseUI;
	IEngineAPI *iEngineAPI;
	//vgui2
	vgui::ILocalize *ivgLocalize;
	vgui::ISystem *ivgSystem;
	vgui::IInput *ivgInput;
	vgui::IInputInternal *ivgInputInternal;
	vgui::IPanel *ivgPanel;
	vgui::IVGui *ivgVGui;
	//FileSystem_Stdio
	IFileSystem *iFileSystem;
};
extern CInterfaceLoader gInterface;








#endif // CInterfaceLoader_h__
