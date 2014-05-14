#ifndef C_ENGINE_LOADER_H
#define C_ENGINE_LOADER_H

#define ENGINE_RESTART_NOTQUITTING 0
#define ENGINE_RESTART_RESTART 1
#define ENGINE_RESTART_FAILURE 2

class CEngineLoader
{
public:
	char *GetEngineLib();
	bool Run(bool CreateMutex=false);
	

	
private:
	void Init();
	bool PreRun(bool bCreateMutex=false);
	void PostRun();
	bool bInitialised;
	char filename[MAX_PATH];
	char *g_pszBaseDirectory;
    char *g_pszGameDirectory;
	int restart;
	HINSTANCE g_hInstance;
	HANDLE Mutex;
};

extern CEngineLoader EngineLoader;
#endif
