
#include "stdafx.h"
#include "DebugHelp.h"
#include "CInterfaceLoader.h"
#include "CEngineLoader.h"
#include "CRegistry.h"
#include "CNullInterface.h"


CInterfaceLoader::CInterfaceLoader()
{
	this->Loaded=false;
}

CInterfaceLoader::~CInterfaceLoader()
{
//	this->ShutDown();
}
void CInterfaceLoader::ShutDown()
{
	
	if(!Loaded)
		return;
	Loaded=false;
	if(true)
	{
		Sys_UnloadModule(mGameUI);
		//Sys_UnloadModule(mEngine);
		Sys_UnloadModule(mVGUI2);
		Sys_UnloadModule(mFileSystem);
	}
	mGameUI=NULL;
	mEngine=NULL;
	mVGUI2=NULL;
	mFileSystem=NULL;
	iEngineAPI=NULL;
	iGameUI=NULL;
	iGameConsole=NULL;
	iRunGameEngine=NULL;
	iBaseUI=NULL;
	ivgLocalize=NULL;
	ivgSystem=NULL;
	ivgInput=NULL;
	ivgInputInternal=NULL;
}
bool CInterfaceLoader::Init()
{
	
	if(this->Loaded)
		return true;

	mEngine=Sys_LoadModule(EngineLoader.GetEngineLib());\
	if(!mEngine)
	{
		Registry.WriteInt("CrashInitializingVideoMode", TRUE);
		return false;
	}
	CreateInterfaceFn mEngineFactory=Sys_GetFactory(mEngine);\
		if(!mEngineFactory) FatalError("Can't get %s factory",EngineLoader.GetEngineLib());
	CREATE_AND_VALIDATE_INTERFACE(iBaseUI,IBaseUI*,mEngine,BASEUI_INTERFACE_VERSION);
	CREATE_AND_VALIDATE_INTERFACE(iEngineAPI,IEngineAPI*,mEngine,VENGINE_LAUNCHER_API_VERSION);

	GET_FACTORY(mGameUI,"valve/cl_dlls/GameUI");
	CREATE_AND_VALIDATE_INTERFACE(iGameUI,IGameUI*,mGameUI,GAMEUI_INTERFACE_VERSION);
	CREATE_AND_VALIDATE_INTERFACE(iGameConsole,IGameConsole *,mGameUI,GAMECONSOLE_INTERFACE_VERSION);
	CREATE_AND_VALIDATE_INTERFACE(iRunGameEngine,IRunGameEngine*,mGameUI,RUNGAMEENGINE_INTERFACE_VERSION);
	
	GET_FACTORY(mVGUI2,"vgui2");
	CREATE_AND_VALIDATE_INTERFACE(ivgLocalize,vgui::ILocalize*,mVGUI2,VGUI_LOCALIZE_INTERFACE_VERSION);
	CREATE_AND_VALIDATE_INTERFACE(ivgSystem,vgui::ISystem*,mVGUI2,VGUI_SYSTEM_INTERFACE_VERSION);
	CREATE_AND_VALIDATE_INTERFACE(ivgInput,vgui::IInput*,mVGUI2,VGUI_INPUT_INTERFACE_VERSION);
	CREATE_AND_VALIDATE_INTERFACE(ivgInputInternal,vgui::IInputInternal*,mVGUI2,VGUI_INPUTINTERNAL_INTERFACE_VERSION);	
	CREATE_AND_VALIDATE_INTERFACE(ivgPanel,vgui::IPanel*,mVGUI2,VGUI_PANEL_INTERFACE_VERSION);
	CREATE_AND_VALIDATE_INTERFACE(ivgVGui,vgui::IVGui*,mVGUI2,VGUI_IVGUI_INTERFACE_VERSION);

	GET_FACTORY(mFileSystem,"FileSystem_Stdio");
	CREATE_AND_VALIDATE_INTERFACE(iFileSystem,IFileSystem*,mFileSystem,FILESYSTEM_INTERFACE_VERSION);
	gFileSystemFactory=mFileSystemFactory;
	this->Loaded=true;
	return true;
}


//Добавлю-ка я "защиту" от вызова интерфейса до инициализации. Мало-ли в глобальном конструкторе будет использоваться кем-то.
IGameUI* CInterfaceLoader::GameUI()
{
	if(!this->Loaded)
		this->Init();
	return this->iGameUI;
}

IGameConsole* CInterfaceLoader::GameConsole()
{
	if(!this->Loaded)
		this->Init();
	return this->iGameConsole;
}

IRunGameEngine* CInterfaceLoader::RunGameEngine()
{
	if(!this->Loaded)
		this->Init();
	return this->iRunGameEngine;
}
//hw
IBaseUI* CInterfaceLoader::BaseUI()
{
	if(!this->Loaded)
		this->Init();
	return this->iBaseUI;
}
IEngineAPI* CInterfaceLoader::EngineAPI()
{
	if(!this->Loaded)
		this->Init();
	return this->iEngineAPI;
}
//vgui2
vgui::ILocalize *CInterfaceLoader::vgLocalize()
{
	if(!this->Loaded)
		this->Init();
	return this->ivgLocalize;
}
vgui::ISystem* CInterfaceLoader::vgSystem()
{
	if(!this->Loaded)
		this->Init();
	return this->ivgSystem;
}
vgui::IInput* CInterfaceLoader::vgInput()
{
	if(!this->Loaded)
		this->Init();
	return this->ivgInput;
}
vgui::IInputInternal* CInterfaceLoader::vgInputInternal()
{
	if(!this->Loaded)
		this->Init();
	return this->ivgInputInternal;
}
vgui::IPanel* CInterfaceLoader::vgPanel()
{
	if(!this->Loaded)
		this->Init();
	return this->ivgPanel;
}
vgui::IVGui* CInterfaceLoader::vgVGui()
{
	if(!this->Loaded)
		this->Init();
	return this->ivgVGui;
}
//FileSystem_Stdio
IFileSystem* CInterfaceLoader::FileSystem()
{
	if(!this->Loaded)
		this->Init();
	return this->iFileSystem;
}



EXPOSE_SINGLE_INTERFACE(CNullInterface,INullInterface,NULL_INTERFACE_VERSION);
CInterfaceLoader gInterface;
