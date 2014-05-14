#include <Meta_Api.h>

cl_enginefunc_t gEngfuncs;
meta_globals_t *gpMetaGlobals;
IMetaInterface *MetaInterface;
int Initialize(cl_enginefunc_t *pEnginefuncs, int iVersion)
{
	gEngfuncs = *(cl_enginefunc_t *)malloc(sizeof(cl_enginefunc_t));
	memcpy(&gEngfuncs, pEnginefuncs, sizeof(cl_enginefunc_t));

	gEngfuncs.pfnClientCmd("echo \"Hello from gEngfuncs!\"");

	RETURN_META_VALUE(MRES_IGNORED, 0);
}

bool FirstFrame=true;
void HUD_Frame( double time )
{
	if(FirstFrame)
	{
		if(MetaInterface)
		{
			MetaInterface->ActivateConsole();
			MetaInterface->ConPrintf("Hello from MetaInterface!\n");
			gEngfuncs.pfnClientCmd("developer 1");
			MetaInterface->ConDPrintf("ConDPrintf test");
			gEngfuncs.pfnClientCmd("developer 0");
		}
	}
	FirstFrame=false;
}

extern "C" int __declspec( dllexport ) Meta_Attach(meta_globals_t *pMGlobals)
{
	gpMetaGlobals = pMGlobals;
	return 1;
}

extern "C" int __declspec( dllexport ) Meta_Detach(void)
{
	return 1;
}

extern "C" int __declspec( dllexport ) GetExportFunctionsTable(cl_clientfunc_t *pClfuncs)
{
	memset(pClfuncs, 0, sizeof(cl_clientfunc_t));

	pClfuncs->Initialize = &Initialize;
	pClfuncs->HUD_Frame = &HUD_Frame;
	return 1;
}


extern "C" int __declspec( dllexport ) GetMetaFactory(CreateInterfaceFn Factory)
{
	MetaInterface=(IMetaInterface*)Factory(META_INTERFACE_VERSION,NULL);
	return 1;
}