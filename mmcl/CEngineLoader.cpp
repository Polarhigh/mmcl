#include "stdafx.h"
#include "CEngineLoader.h"
#include "CInterfaceLoader.h"
#include "CParms.h"
#include "CRegistry.h"
#include "DebugHelp.h"



CEngineLoader EngineLoader;

bool CEngineLoader::Init()
{
	if(this->Initialised())
		return true;
	if(!Parms.Initialised())
		Parms.Init(GetCommandLineA());
	if(!Registry.Initialised())
		if(!Registry.Init())
			FatalError("Can't init registry");
	if (Parms.Check("-soft") || Parms.Check("-software"))
		Registry.WriteString("EngineDLL", "sw.dll");
	else if (Parms.Check("-gl") || Parms.Check("-d3d"))
		Registry.WriteString("EngineDLL", "hw.dll");

	this->bInitialised=true;
	return true;
}

bool CEngineLoader::Initialised()
{
	return bInitialised;
}

char *CEngineLoader::GetEngineLib()
{
	if(!this->Initialised())
		if(!this->Init())
			FatalError("Can't init CEngineLoader");

		return Registry.ReadString("EngineDLL", "hw.dll");
}

bool CEngineLoader::PreRun(bool bCreateMutex)
{
	if(bCreateMutex)
	{
		this->Mutex = CreateMutexA(NULL, NULL, "ValveHalfLifeLauncherMutex");
		DWORD status = WaitForSingleObject(this->Mutex, NULL);

		if (status && status != WAIT_ABANDONED)
		{
			FatalError("Could not launch game.\nOnly one instance of this game can be run at a time.");
		}
	}
	
	GetModuleFileNameA(NULL, filename, MAX_PATH);
	char *value = strrchr(filename, '\\') + 1;

	if (_stricmp(value, "hl.exe") && !Parms.Check("-game"))
	{
		value[strlen(value) - 4] = '\0';
		//Parms.Append("-game", value);
		Parms.Append("-game", "cstrike");
	}

	value = Parms.Check("-game");
	
	if (value && !_stricmp(value, "czero"))
		Parms.Append("-forcevalve");

	g_pszGameDirectory = value;

	do 
	{
		if (Registry.ReadInt("CrashInitializingVideoMode", FALSE))
		{
			Registry.WriteInt("CrashInitializingVideoMode", FALSE);
			auto streng=Registry.ReadString("EngineDLL", "hw.dll");
			if (strcmp(streng, "hw.dll")==0)
			{
				if (Registry.ReadInt("EngineD3D", FALSE))
				{
					Registry.WriteInt("EngineD3D", FALSE);

					if (MessageBoxA(NULL, "The game has detected that the previous attempt to start in D3D video mode failed.\nThe game will now run attempt to run in openGL mode.", "Video mode change failure", MB_OKCANCEL | MB_ICONWARNING) != IDOK)
						return false;
				}
				else
				{
					Registry.WriteString("EngineDLL", "sw.dll");

					if (MessageBoxA(NULL, "The game has detected that the previous attempt to start in openGL video mode failed.\nThe game will now run in software mode.", "Video mode change failure", MB_OKCANCEL | MB_ICONWARNING) != IDOK)
						return false;
				}

				Registry.WriteInt("ScreenWidth", 640);
				Registry.WriteInt("ScreenHeight", 480);
				Registry.WriteInt("ScreenBPP", 16);
			}
			else
			{
				 Registry.WriteString("EngineDLL", "hw.dll");
				 Registry.WriteInt("EngineD3D", FALSE);
				 if (MessageBoxA(NULL, "The game has detected that the previous attempt to start in software video mode failed.\nThe game will now run in openGL mode.", "Video mode change failure", MB_OKCANCEL | MB_ICONWARNING) != IDOK)
					 return false;

				 Registry.WriteInt("ScreenWidth", 640);
				 Registry.WriteInt("ScreenHeight", 480);
				 Registry.WriteInt("ScreenBPP", 32);
			}
		}
	}
	while(!gInterface.Initialised(true));

	char *path = NULL;
	GetLongPathNameA(filename, filename, MAX_PATH);

	if (!path)
	{
		path = strrchr(filename, '\\');
		*path++ = '\0';
		g_pszBaseDirectory = filename;
	}


	return true;
}

void CEngineLoader::PostRun()
{
	WSACleanup();
	ReleaseMutex(this->Mutex);
	CloseHandle(this->Mutex);
	Parms.Shutdown();
	Registry.Shutdown();
}

bool CEngineLoader::Run()
{
	this->Init();
	while (1)
	{
		if(!EngineLoader.PreRun(true))
		{
			this->PostRun();
			return false;
		}
		static char retCmdLine[128];
		Registry.WriteInt("CrashInitializingVideoMode", TRUE);
		int restart = gInterface.EngineAPI()->Run(g_hInstance, g_pszBaseDirectory, Parms.GetCommandLine(), retCmdLine, Sys_GetFactoryThis(), gInterface.FileSystemFactory());
		
		
		gInterface.ShutDown(true);
		Sys_UnloadModule(Sys_LoadModule("client.dll"));//так надо.
		Registry.WriteInt("CrashInitializingVideoMode", FALSE);
		if (restart == ENGINE_RESTART_NOTQUITTING || restart > ENGINE_RESTART_FAILURE)
			break;

		switch (restart)
		{
			case ENGINE_RESTART_RESTART: break;
			case ENGINE_RESTART_FAILURE:
			{
				Registry.WriteInt("ScreenWidth", 640);
				Registry.WriteInt("ScreenHeight", 480);
				Registry.WriteInt("ScreenBPP", 16);
				Registry.WriteString("EngineDLL", "sw.dll");

				if (MessageBoxA(NULL, "The specified video mode is not supported.\nThe game will now run in software mode.", "Video mode change failure", MB_OKCANCEL | MB_ICONWARNING) != IDOK)
					break;
			}
		}

		Parms.Remove("-sw");
		Parms.Remove("-startwindowed");
		Parms.Remove("-windowed");
		Parms.Remove("-window");
		Parms.Remove("-full");
		Parms.Remove("-fullscreen");
		Parms.Remove("-soft");
		Parms.Remove("-software");
		Parms.Remove("-gl");
		Parms.Remove("-d3d");
		Parms.Remove("-w");
		Parms.Remove("-width");
		Parms.Remove("-h");
		Parms.Remove("-height");
		Parms.Append("-novid");

		if (strstr(retCmdLine, "-game"))
			Parms.Remove("-game");

		if (strstr(retCmdLine, "+load"))
			Parms.Remove("+load");

		Parms.Append(retCmdLine);
	}
	this->PostRun();
}


