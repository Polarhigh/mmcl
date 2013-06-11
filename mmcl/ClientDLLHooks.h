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

#pragma once

#include <Windows.h>
#define HSPRITE DeletedWinapi_HSPRITE
#include <wrect.h>
#include <cl_dll.h>
#include <r_efx.h>
#include "Meta_Api.h"

// ===== macros for void-returning functions ==================================

// declare/init some variables
#define SETUP_API_CALLS_void(FN_TYPE, pfnName) \
	unsigned int i; \
	META_RES mres=MRES_UNSET, status=MRES_UNSET, prev_mres=MRES_UNSET; \
	FN_TYPE pfn_routine=NULL; \
	memset(gpMetaGlobals, 0, sizeof(gpMetaGlobals));

// call each plugin
#define CALL_PLUGIN_API_void(post, pfnName, pfn_args) \
	prev_mres=MRES_UNSET; \
	for(i=0; i < gPluginsHModule.size(); i++) { \
		if (!post) { \
			if (gPluginsClFuncs[i] && (pfn_routine=gPluginsClFuncs[i]->pfnName)); \
			else \
				/* plugin doesn't provide this function */ \
				continue; \
		} \
		else { \
			if (gPluginsClFuncs_Post[i] && (pfn_routine=gPluginsClFuncs_Post[i]->pfnName)); \
			else \
				/* plugin doesn't provide this function */ \
				continue; \
		} \
		/* initialize gpMetaGlobals */ \
		gpMetaGlobals->mres = MRES_UNSET; \
		gpMetaGlobals->prev_mres = prev_mres; \
		gpMetaGlobals->status = status; \
		/* call plugin */ \
		pfn_routine pfn_args; \
		/* plugin's result code */ \
		mres=gpMetaGlobals->mres; \
		if(mres > status) \
			status = mres; \
		/* save this for successive plugins to see */ \
		prev_mres = mres; \
	}

// call "real" function, from gamedll
#define CALL_GAME_API_void(pfnName, pfn_args) \
	if(status==MRES_SUPERCEDE) { \
		/* don't return here; superceded game routine, but still allow \
		 * _post routines to run. \
		 */ \
	} \
	else { \
		DisableRedirect(&ghClfuncs[CLF_##pfnName]); \
		gClfuncs.pfnName pfn_args; \
		EnableRedirect(&ghClfuncs[CLF_##pfnName]); \
	}

// return (void)
#define RETURN_API_void() \
	return;

// ===== macros for type-returning functions ==================================

// declare/init some variables
#define SETUP_API_CALLS(ret_t, ret_init, FN_TYPE, pfnName) \
	unsigned int i; \
	ret_t dllret=ret_init; \
	ret_t override_ret=ret_init; \
	ret_t pub_override_ret=ret_init; \
	ret_t orig_ret=ret_init; \
	ret_t pub_orig_ret=ret_init; \
	META_RES mres=MRES_UNSET, status=MRES_UNSET, prev_mres=MRES_UNSET; \
	FN_TYPE pfn_routine=NULL; \

// call each plugin
#define CALL_PLUGIN_API(post, ret_init, pfnName, pfn_args, MRES_TYPE) \
	override_ret=ret_init; \
	prev_mres=MRES_UNSET; \
	for(i=0; i < gPluginsHModule.size(); i++) { \
		if (!post) { \
			if (gPluginsClFuncs[i] && (pfn_routine=gPluginsClFuncs[i]->pfnName)); \
			else \
				/* plugin doesn't provide this function */ \
				continue; \
		} \
		else { \
			if (gPluginsClFuncs_Post[i] && (pfn_routine=gPluginsClFuncs_Post[i]->pfnName)); \
			else \
				/* plugin doesn't provide this function */ \
				continue; \
		} \
		/* initialize gpMetaGlobals */ \
		gpMetaGlobals->mres = MRES_UNSET; \
		gpMetaGlobals->prev_mres = prev_mres; \
		gpMetaGlobals->status = status; \
		pub_orig_ret = orig_ret; \
		gpMetaGlobals->orig_ret = &pub_orig_ret; \
		if(status==MRES_TYPE) { \
			pub_override_ret = override_ret; \
			gpMetaGlobals->override_ret = &pub_override_ret; \
		} \
		/* call plugin */ \
		dllret=pfn_routine pfn_args; \
		/* plugin's result code */ \
		mres=gpMetaGlobals->mres; \
		if(mres > status) \
			status = mres; \
		/* save this for successive plugins to see */ \
		prev_mres = mres; \
		if(mres==MRES_TYPE) \
			override_ret = pub_override_ret = dllret; \
	}

// call "real" function, from gamedll
#define CALL_GAME_API(pfnName, pfn_args) \
	if(status==MRES_SUPERCEDE) { \
		orig_ret = pub_orig_ret = override_ret; \
		gpMetaGlobals->orig_ret = &pub_orig_ret; \
		/* don't return here; superceded game routine, but still allow \
		 * _post routines to run. \
		 */ \
	} \
	else { \
		DisableRedirect(&ghClfuncs[CLF_##pfnName]); \
		dllret=gClfuncs.pfnName pfn_args; \
		EnableRedirect(&ghClfuncs[CLF_##pfnName]); \
		orig_ret = dllret; \
	}

// return a value
#define RETURN_API() \
	if(status==MRES_OVERRIDE) \
		return(override_ret); \
	else \
		return(orig_ret);

enum clfuncs_e
{
	CLF_Initialize = 0,
	CLF_HUD_Init,
	CLF_HUD_VidInit,
	CLF_HUD_Redraw,
	CLF_HUD_UpdateClientData,
	CLF_HUD_Reset,
	CLF_HUD_PlayerMove,
	CLF_HUD_PlayerMoveInit,
	CLF_HUD_PlayerMoveTexture,
	CLF_IN_ActivateMouse,
	CLF_IN_DeactivateMouse,
	CLF_IN_MouseEvent,
	CLF_IN_ClearStates,
	CLF_IN_Accumulate,
	CLF_CL_CreateMove,
	CLF_CL_IsThirdPerson,
	CLF_CL_CameraOffset,
	CLF_KB_Find,
	CLF_CAM_Think,
	CLF_V_CalcRefdef,
	CLF_HUD_AddEntity,
	CLF_HUD_CreateEntities,
	CLF_HUD_DrawNormalTriangles,
	CLF_HUD_DrawTransparentTriangles,
	CLF_HUD_StudioEvent,
	CLF_HUD_PostRunCmd,
	CLF_HUD_Shutdown,
	CLF_HUD_TxferLocalOverrides,
	CLF_HUD_ProcessPlayerState,
	CLF_HUD_TxferPredictionData,
	CLF_Demo_ReadBuffer,
	CLF_HUD_ConnectionlessPacket,
	CLF_HUD_GetHullBounds,
	CLF_HUD_Frame,
	CLF_HUD_Key_Event,
	CLF_HUD_TempEntUpdate,
	CLF_HUD_GetUserEntity,
	CLF_HUD_VoiceStatus,
	CLF_HUD_DirectorMessage,
	CLF_HUD_GetStudioModelInterface,

	CLF_End
};

extern cl_enginefunc_t gEngfuncs;

void CreateHooks(void);