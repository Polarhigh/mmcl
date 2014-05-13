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
#include "stdafx.h"
#include "ClientDLLHooks.h"
#include "Plugins.h"
#include "Types.h"


meta_globals_t *gpMetaGlobals;

vector<HMODULE> gPluginsHModule;
vector<cl_clientfunc_t *> gPluginsClFuncs;
vector<cl_clientfunc_t *> gPluginsClFuncs_Post;
vector<META_ATTACH_FN> gPluginsMetaAttach;
vector<META_DETACH_FN> gPluginsMetaDetach;

void LoadPlugins()
{
	gpMetaGlobals = new meta_globals_t;

	ifstream file;
	file.open("mmcl/plugins.ini");

	if (!file.is_open())
		return;

	while (!file.eof())
	{
		string sPath;
		HMODULE hPlugin;

		getline(file, sPath);
		if (sPath.c_str()[0] == ';') continue;
		
		hPlugin = LoadLibraryA(sPath.c_str());
		if (hPlugin == NULL) continue;

		gPluginsHModule.push_back(hPlugin);

		META_ATTACH_FN pMetaAttach = (META_ATTACH_FN)GetProcAddress(hPlugin, "Meta_Attach");
		META_DETACH_FN pMetaDetach = (META_DETACH_FN)GetProcAddress(hPlugin, "Meta_Detach");

		if (pMetaAttach != NULL) pMetaAttach(gpMetaGlobals);

		gPluginsMetaAttach.push_back(pMetaAttach);
		gPluginsMetaDetach.push_back(pMetaDetach);

		tGetExportFunctionsTable pFunc = (tGetExportFunctionsTable)GetProcAddress(hPlugin, "GetExportFunctionsTable");
		tGetExportFunctionsTable pFunc_Post = (tGetExportFunctionsTable)GetProcAddress(hPlugin, "GetExportFunctionsTable_Post");
		cl_clientfunc_t *pExportFuncs = (cl_clientfunc_t *)malloc(sizeof(cl_clientfunc_t));
		cl_clientfunc_t *pExportFuncs_Post = (cl_clientfunc_t *)malloc(sizeof(cl_clientfunc_t));
		memset(pExportFuncs, NULL, sizeof(cl_clientfunc_t));
		memset(pExportFuncs_Post, NULL, sizeof(cl_clientfunc_t));

		if (pFunc != NULL) pFunc(pExportFuncs);
		if (pFunc_Post != NULL) pFunc_Post(pExportFuncs_Post);

		gPluginsClFuncs.push_back(pExportFuncs);
		gPluginsClFuncs_Post.push_back(pExportFuncs_Post);
	}

	file.close();
}
