#include "Meta_Api.h"

cl_enginefunc_t gEngfuncs;
meta_globals_t *gpMetaGlobals;

int Initialize(cl_enginefunc_t *pEnginefuncs, int iVersion)
{
	gEngfuncs = *(cl_enginefunc_t *)malloc(sizeof(cl_enginefunc_t));
	memcpy(&gEngfuncs, pEnginefuncs, sizeof(cl_enginefunc_t));

	gEngfuncs.pfnClientCmd("echo \"Hello world!\"");

	RETURN_META_VALUE(MRES_IGNORED, 0);
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

	return 1;
}
