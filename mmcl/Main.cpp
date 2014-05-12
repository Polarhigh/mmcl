/* Metamod:Client
*
*  by the Metamod:Client Development team
*
*  This program is free software; you can redistribute it and/or modify it
*  under the terms of the GNU General Public License as published by the
*  Free Software Foundation; either version 2 of the License, or (at
*  your option) any later version.
*
*  This program is distributed in the hope that it will be useful, but
*  WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
*  General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software Foundation,
*  Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*
*  In addition, as a special exception, the author gives permission to
*  link the code of this program with the Half-Life Game Engine ("HL
*  Engine") and Modified Game Libraries ("MODs") developed by Valve,
*  L.L.C ("Valve"). You must obey the GNU General Public License in all
*  respects for all of the code used other than the HL Engine and MODs
*  from Valve. If you modify this file, you may extend this exception
*  to your version of the file, but you are not obligated to do so. If
*  you do not wish to do so, delete this exception statement from your
*  version.
*/



#include "ClientDLLHooks.h"
#include "Hooks.h"
#include "Plugins.h"
#include "interface.h"
#include "Main.h"

hook hLoadLibraryA;
int giLoaded = 0;

HMODULE WINAPI LoadLibraryA_HookHandler(LPCTSTR lpFileName)
{
	DisableRedirect(&hLoadLibraryA);
	HMODULE hRet = LoadLibraryA(lpFileName);
	EnableRedirect(&hLoadLibraryA);

	if (GetModuleHandleA("client.dll") != NULL && !giLoaded)
	{
		giLoaded = 1;
		CreateHooks();
		LoadPlugins();
		DisableRedirect(&hLoadLibraryA);
	}

	return hRet;
}



int APIENTRY DllMain(HMODULE hDLL, DWORD Reason, LPVOID Reserved)
{
	switch(Reason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hDLL);
		RedirectFunction(&hLoadLibraryA, LoadLibraryA, LoadLibraryA_HookHandler);
		break;
	case DLL_PROCESS_DETACH:
		for (unsigned int i = 0; i < gPluginsHModule.size(); i++)
		{
			if (gPluginsMetaDetach[i] != NULL) gPluginsMetaDetach[i]();
			FreeLibrary(gPluginsHModule[i]);
		}
		break;
	}

	return TRUE;
}


/*Basis for .asi
Doesn't used yet because we need to find some other way to get cl_enginefunc_t address
Initialize_HookHandler hook would not work, because .asi-files loads after it.
*/
EXPORT_FUNCTION S32 AILCALL RIB_Main(	
	HPROVIDER provider_handle,
	U32 up_down,
	RIB_alloc_provider_handle_ptr RIB_alloc_provider_handle,
	RIB_register_interface_ptr RIB_register_interface,
	RIB_unregister_interface_ptr RIB_unregister_interface
	)
{
		
		if (up_down)
		{
			
		}
		else
		{
			
		}
		return TRUE;
}

extern "C" int __declspec( dllexport ) Init() { return 1; }