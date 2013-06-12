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
#include "Types.h"

cl_clientfunc_t gClfuncs;
cl_enginefunc_t gEngfuncs;

hook ghClfuncs[CLF_End];

#define P_PRE 0
#define P_POST 1

#define REDIRECT(x,y) RedirectFunction(&ghClfuncs[CLF_##x], (LPVOID)GetProcAddress(hClientDll, #x), (LPVOID)##y); \
				gClfuncs.##x = (t##x)ghClfuncs[CLF_##x].pAddress;

#define META_DLLAPI_HANDLE_void(pfnName, pfn_args) \
	SETUP_API_CALLS_void(t##pfnName, pfnName); \
	CALL_PLUGIN_API_void(P_PRE, pfnName, pfn_args); \
	CALL_GAME_API_void(pfnName, pfn_args); \
	CALL_PLUGIN_API_void(P_POST, pfnName, pfn_args);

#define META_DLLAPI_HANDLE(ret_t, ret_init, pfnName, pfn_args) \
	SETUP_API_CALLS(ret_t, ret_init, t##pfnName, pfnName); \
	CALL_PLUGIN_API(P_PRE, ret_init, pfnName, pfn_args, MRES_SUPERCEDE); \
	CALL_GAME_API(pfnName, pfn_args); \
	CALL_PLUGIN_API(P_POST, ret_init, pfnName, pfn_args, MRES_OVERRIDE);

int Initialize_HookHandler(cl_enginefunc_t *pEnginefuncs, int iVersion)
{
	gEngfuncs = *(cl_enginefunc_t *)malloc(sizeof(cl_enginefunc_t));
	memcpy(&gEngfuncs, pEnginefuncs, sizeof(cl_enginefunc_t));

	META_DLLAPI_HANDLE(int, 0, Initialize, (pEnginefuncs, iVersion))
	RETURN_API()
}

void HUD_Init_HookHandler(void)
{
	META_DLLAPI_HANDLE_void(HUD_Init, ())
	RETURN_API_void()
}

int HUD_VidInit_HookHandler(void)
{
	META_DLLAPI_HANDLE(int, 0, HUD_VidInit, ())
	RETURN_API()
}

int HUD_Redraw_HookHandler(float flTime, int iIntermission)
{
	META_DLLAPI_HANDLE(int, 0, HUD_Redraw, (flTime, iIntermission))
	RETURN_API()
}

int HUD_UpdateClientData_HookHandler(client_data_t *cdata, float flTime)
{
	META_DLLAPI_HANDLE(int, 0, HUD_UpdateClientData, (cdata, flTime))
	RETURN_API()
}

void HUD_Reset_HookHandler(void)
{
	META_DLLAPI_HANDLE_void(HUD_Reset, ())
	RETURN_API_void()
}

void HUD_PlayerMove_HookHandler(struct playermove_s *ppmove, int server)
{
	META_DLLAPI_HANDLE_void(HUD_PlayerMove, (ppmove, server))
	RETURN_API_void()
}

void HUD_PlayerMoveInit_HookHandler(struct playermove_s *ppmove)
{
	META_DLLAPI_HANDLE_void(HUD_PlayerMoveInit, (ppmove))
	RETURN_API_void()
}

char HUD_PlayerMoveTexture_HookHandler(char *name)
{
	META_DLLAPI_HANDLE(char, NULL, HUD_PlayerMoveTexture, (name))
	RETURN_API()
}

void IN_ActivateMouse_HookHandler(void)
{
	META_DLLAPI_HANDLE_void(IN_ActivateMouse, ())
	RETURN_API_void()
}

void IN_DeactivateMouse_HookHandler(void)
{
	META_DLLAPI_HANDLE_void(IN_DeactivateMouse, ())
	RETURN_API_void()
}

void IN_MouseEvent_HookHandler(int mstate)
{
	META_DLLAPI_HANDLE_void(IN_MouseEvent, (mstate))
	RETURN_API_void()
}

void IN_ClearStates_HookHandler(void)
{
	META_DLLAPI_HANDLE_void(IN_ClearStates, ())
	RETURN_API_void()
}

void IN_Accumulate_HookHandler(void)
{
	META_DLLAPI_HANDLE_void(IN_Accumulate, ())
	RETURN_API_void()
}

void CL_CreateMove_HookHandler(float frametime, struct usercmd_s *cmd, int active)
{
	META_DLLAPI_HANDLE_void(CL_CreateMove, (frametime, cmd, active))
	RETURN_API_void()
}

int CL_IsThirdPerson_HookHandler(void)
{
	META_DLLAPI_HANDLE(int, 0, CL_IsThirdPerson, ())
	RETURN_API()
}

void CL_CameraOffset_HookHandler(float *ofs)
{
	META_DLLAPI_HANDLE_void(CL_CameraOffset, (ofs))
	RETURN_API_void()
}

struct kbutton_s *KB_Find_HookHandler(const char *name)
{
	META_DLLAPI_HANDLE(struct kbutton_s *, NULL, KB_Find, (name))
	RETURN_API()
}

void CAM_Think_HookHandler(void)
{
	META_DLLAPI_HANDLE_void(CAM_Think, ())
	RETURN_API_void()
}

void V_CalcRefdef_HookHandler(struct ref_params_s* pparams)
{
	META_DLLAPI_HANDLE_void(V_CalcRefdef, (pparams))
	RETURN_API_void()
}

int HUD_AddEntity_HookHandler(int type, struct cl_entity_s *ent, const char *modelname)
{
	META_DLLAPI_HANDLE(int, 0, HUD_AddEntity, (type, ent, modelname))
	RETURN_API()
}

void HUD_CreateEntities_HookHandler(void)
{
	META_DLLAPI_HANDLE_void(HUD_CreateEntities, ())
	RETURN_API_void()
}

void HUD_DrawNormalTriangles_HookHandler(void)
{
	META_DLLAPI_HANDLE_void(HUD_DrawNormalTriangles, ())
	RETURN_API_void()
}

void HUD_DrawTransparentTriangles_HookHandler(void)
{
	META_DLLAPI_HANDLE_void(HUD_DrawTransparentTriangles, ())
	RETURN_API_void()
}

void HUD_StudioEvent_HookHandler(const struct mstudioevent_s *event, const struct cl_entity_s *entity)
{
	META_DLLAPI_HANDLE_void(HUD_StudioEvent, (event, entity))
	RETURN_API_void()
}

void HUD_PostRunCmd_HookHandler(struct local_state_s *from, struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed)
{
	META_DLLAPI_HANDLE_void(HUD_PostRunCmd, (from, to, cmd, runfuncs, time, random_seed))
	RETURN_API_void()
}

void HUD_Shutdown_HookHandler(void)
{
	META_DLLAPI_HANDLE_void(HUD_Shutdown, ())
	RETURN_API_void()
}

void HUD_TxferLocalOverrides_HookHandler(struct entity_state_s *state, const struct clientdata_s *client)
{
	META_DLLAPI_HANDLE_void(HUD_TxferLocalOverrides, (state, client))
	RETURN_API_void()
}

void HUD_ProcessPlayerState_HookHandler(struct entity_state_s *dst, const struct entity_state_s *src)
{
	META_DLLAPI_HANDLE_void(HUD_ProcessPlayerState, (dst, src))
	RETURN_API_void()
}

void HUD_TxferPredictionData_HookHandler(struct entity_state_s *ps, const struct entity_state_s *pps, struct clientdata_s *pcd, const struct clientdata_s *ppcd, struct weapon_data_s *wd, const struct weapon_data_s *pwd)
{
	META_DLLAPI_HANDLE_void(HUD_TxferPredictionData, (ps, pps, pcd, ppcd, wd, pwd))
	RETURN_API_void()
}

void Demo_ReadBuffer_HookHandler(int size, unsigned char *buffer)
{
	META_DLLAPI_HANDLE_void(Demo_ReadBuffer, (size, buffer))
	RETURN_API_void()
}

int HUD_ConnectionlessPacket_HookHandler(struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size)
{
	META_DLLAPI_HANDLE(int, 0, HUD_ConnectionlessPacket, (net_from, args, response_buffer, response_buffer_size))
	RETURN_API()
}

int HUD_GetHullBounds_HookHandler(int hullnumber, float *mins, float *maxs)
{
	META_DLLAPI_HANDLE(int, 0, HUD_GetHullBounds, (hullnumber, mins, maxs))
	RETURN_API()
}

void HUD_Frame_HookHandler(double time)
{
	META_DLLAPI_HANDLE_void(HUD_Frame, (time))
	RETURN_API_void()
}

int HUD_Key_Event_HookHandler(int eventcode, int keynum, const char *pszCurrentBinding)
{
	META_DLLAPI_HANDLE(int, 0, HUD_Key_Event, (eventcode, keynum, pszCurrentBinding))
	RETURN_API()
}

void HUD_TempEntUpdate_HookHandler(double frametime,double client_time, double cl_gravity, TEMPENTITY **ppTempEntFree, TEMPENTITY **ppTempEntActive, int ( *Callback_AddVisibleEntity )( cl_entity_t *pEntity ), void ( *Callback_TempEntPlaySound )( TEMPENTITY *pTemp, float damp ))
{
	META_DLLAPI_HANDLE_void(HUD_TempEntUpdate, (frametime, client_time, cl_gravity, ppTempEntFree, ppTempEntActive, Callback_AddVisibleEntity, Callback_TempEntPlaySound))
	RETURN_API_void()
}

struct cl_entity_s *HUD_GetUserEntity_HookHandler(int index)
{
	META_DLLAPI_HANDLE(struct cl_entity_s *, NULL, HUD_GetUserEntity, (index))
	RETURN_API()
}

int HUD_VoiceStatus_HookHandler(int entindex, qboolean bTalking)
{
	META_DLLAPI_HANDLE(int, 0, HUD_VoiceStatus, (entindex, bTalking))
	RETURN_API()
}

void HUD_DirectorMessage_HookHandler(int iSize, void *pbuf)
{
	META_DLLAPI_HANDLE_void(HUD_DirectorMessage, (iSize, pbuf))
	RETURN_API_void()
}

int HUD_GetStudioModelInterface_HookHandler(int version, struct r_studio_interface_s **ppinterface, struct engine_studio_api_s *pstudio)
{
	META_DLLAPI_HANDLE(int, 0, HUD_GetStudioModelInterface, (version, ppinterface, pstudio))
	RETURN_API()
}

void CreateHooks(void)
{
	HMODULE hClientDll = GetModuleHandle("client.dll");

	REDIRECT(Initialize, Initialize_HookHandler);
	REDIRECT(HUD_Init, HUD_Init_HookHandler);
	REDIRECT(HUD_VidInit, HUD_VidInit_HookHandler);
	REDIRECT(HUD_Redraw, HUD_Redraw_HookHandler);
	REDIRECT(HUD_UpdateClientData, HUD_UpdateClientData_HookHandler);
	REDIRECT(HUD_Reset, HUD_Reset_HookHandler);
	REDIRECT(HUD_PlayerMove, HUD_PlayerMove_HookHandler)
	REDIRECT(HUD_PlayerMoveInit, HUD_PlayerMoveInit_HookHandler)
	REDIRECT(HUD_PlayerMoveTexture, HUD_PlayerMoveTexture_HookHandler)
	REDIRECT(IN_ActivateMouse, IN_ActivateMouse_HookHandler)
	REDIRECT(IN_DeactivateMouse, IN_DeactivateMouse_HookHandler)
	REDIRECT(IN_MouseEvent, IN_MouseEvent_HookHandler)
	REDIRECT(IN_ClearStates, IN_ClearStates_HookHandler)
	REDIRECT(IN_Accumulate, IN_Accumulate_HookHandler)
	REDIRECT(CL_CreateMove, CL_CreateMove_HookHandler)
	REDIRECT(CL_IsThirdPerson, CL_IsThirdPerson_HookHandler)
	REDIRECT(CL_CameraOffset, CL_CameraOffset_HookHandler)
	REDIRECT(KB_Find, KB_Find_HookHandler)
	REDIRECT(CAM_Think, CAM_Think_HookHandler)
	REDIRECT(V_CalcRefdef, V_CalcRefdef_HookHandler)
	REDIRECT(HUD_AddEntity, HUD_AddEntity_HookHandler)
	REDIRECT(HUD_CreateEntities, HUD_CreateEntities_HookHandler)
	REDIRECT(HUD_DrawNormalTriangles, HUD_DrawNormalTriangles_HookHandler)
	REDIRECT(HUD_DrawTransparentTriangles, HUD_DrawTransparentTriangles_HookHandler)
	REDIRECT(HUD_StudioEvent, HUD_StudioEvent_HookHandler)
	REDIRECT(HUD_PostRunCmd, HUD_PostRunCmd_HookHandler)
	REDIRECT(HUD_Shutdown, HUD_Shutdown_HookHandler)
	REDIRECT(HUD_TxferLocalOverrides, HUD_TxferLocalOverrides_HookHandler)
	REDIRECT(HUD_ProcessPlayerState, HUD_ProcessPlayerState_HookHandler)
	REDIRECT(HUD_TxferPredictionData, HUD_TxferPredictionData_HookHandler)
	REDIRECT(Demo_ReadBuffer, Demo_ReadBuffer_HookHandler)
	REDIRECT(HUD_ConnectionlessPacket, HUD_ConnectionlessPacket_HookHandler)
	REDIRECT(HUD_GetHullBounds, HUD_GetHullBounds_HookHandler)
	REDIRECT(HUD_Frame, HUD_Frame_HookHandler)
	REDIRECT(HUD_Key_Event, HUD_Key_Event_HookHandler)
	REDIRECT(HUD_TempEntUpdate, HUD_TempEntUpdate_HookHandler)
	REDIRECT(HUD_GetUserEntity, HUD_GetUserEntity_HookHandler)
	REDIRECT(HUD_VoiceStatus, HUD_VoiceStatus_HookHandler)
	REDIRECT(HUD_DirectorMessage, HUD_DirectorMessage_HookHandler)
	REDIRECT(HUD_GetStudioModelInterface, HUD_GetStudioModelInterface_HookHandler)
}
