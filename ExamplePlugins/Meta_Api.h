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
#include <cl_entity.h>
#include <com_model.h>
#include <cvardef.h>
#include <demo_api.h>
#include <ivoicetweak.h>
#include <net_api.h>
#include <particledef.h>
#include <pmtrace.h>
#include <r_efx.h>
#include <r_studioint.h>
#include <ref_params.h>
#include <triangleapi.h>
#include <usercmd.h>
#include <weaponinfo.h>

typedef enum {
	MRES_UNSET = 0,
	MRES_IGNORED,		// plugin didn't take any action
	MRES_HANDLED,		// plugin did something, but real function should still be called
	MRES_OVERRIDE,		// call real function, but use my return value
	MRES_SUPERCEDE,		// skip real function; use my return value
} META_RES;

// Variables provided to plugins.
typedef struct meta_globals_s {
	META_RES mres;			// writable; plugin's return flag
	META_RES prev_mres;		// readable; return flag of the previous plugin called
	META_RES status;		// readable; "highest" return flag so far
	void *orig_ret;			// readable; return value from "real" function
	void *override_ret;		// readable; return value from overriding/superceding plugin
} meta_globals_t;

extern meta_globals_t *gpMetaGlobals;

#define SET_META_RESULT(result)			gpMetaGlobals->mres=result
#define RETURN_META(result) \
	do { gpMetaGlobals->mres=result; return; } while(0)
#define RETURN_META_VALUE(result, value) \
	do { gpMetaGlobals->mres=result; return(value); } while(0)
#define META_RESULT_STATUS				gpMetaGlobals->status
#define META_RESULT_PREVIOUS			gpMetaGlobals->prev_mres
#define META_RESULT_ORIG_RET(type)		*(type *)gpMetaGlobals->orig_ret
#define META_RESULT_OVERRIDE_RET(type)	*(type *)gpMetaGlobals->override_ret

typedef struct cl_clientfunc_s
{
	int( *Initialize )( cl_enginefunc_t *, int );
	void( *HUD_Init )( void );
	int( *HUD_VidInit )( void );
	int( *HUD_Redraw )( float, int );
	int( *HUD_UpdateClientData )( client_data_t *, float );
	void( *HUD_Reset )( void );
	void( *HUD_PlayerMove )( struct playermove_s *, int );
	void( *HUD_PlayerMoveInit )( struct playermove_s * );
	char( *HUD_PlayerMoveTexture )( char * );
	void( *IN_ActivateMouse )( void );
	void( *IN_DeactivateMouse )( void );
	void( *IN_MouseEvent )( int mstate );
	void( *IN_ClearStates )( void );
	void( *IN_Accumulate )( void );
	void( *CL_CreateMove )( float frametime, struct usercmd_s *cmd, int active );
	int( *CL_IsThirdPerson )( void );
	void( *CL_CameraOffset )( float *ofs );
	struct kbutton_s *( *KB_Find )( const char *name );
	void( *CAM_Think )( void );
	void( *V_CalcRefdef )( struct ref_params_s *pparams );
	int( *HUD_AddEntity )( int, struct cl_entity_s *, const char * );
	void( *HUD_CreateEntities )( void );
	void( *HUD_DrawNormalTriangles )( void );
	void( *HUD_DrawTransparentTriangles )( void );
	void( *HUD_StudioEvent )( const struct mstudioevent_s *, const struct cl_entity_s * );
	void( *HUD_PostRunCmd )( struct local_state_s *from, struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed );
	void( *HUD_Shutdown )( void );
	void( *HUD_TxferLocalOverrides )( struct entity_state_s *, const struct clientdata_s * );
	void( *HUD_ProcessPlayerState )( struct entity_state_s *, const struct entity_state_s * );
	void( *HUD_TxferPredictionData )( struct entity_state_s *, const struct entity_state_s *, struct clientdata_s *, const struct clientdata_s *, struct weapon_data_s *, const struct weapon_data_s * );
	void( *Demo_ReadBuffer )( int, unsigned char * );
	int( *HUD_ConnectionlessPacket )( struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size );
	int( *HUD_GetHullBounds )( int hullnumber, float *mins, float *maxs );
	void( *HUD_Frame )( double time );
	int( *HUD_Key_Event )( int, int, const char * );
	void( *HUD_TempEntUpdate )( double, double, double, struct tempent_s **, struct tempent_s **, int( *Callback_AddVisibleEntity )( struct cl_entity_s *pEntity ), void( *Callback_TempEntPlaySound )( struct tempent_s *pTemp, float damp ) );
	struct cl_entity_s *( *HUD_GetUserEntity )( int index );
	int( *HUD_VoiceStatus )( int entindex, qboolean bTalking );
	void( *HUD_DirectorMessage )( int iSize, void *pbuf );
	int( *HUD_GetStudioModelInterface )( int version, struct r_studio_interface_s **ppinterface, struct engine_studio_api_s *pstudio );
} cl_clientfunc_t;

extern "C" int __declspec( dllexport ) Meta_Attach(meta_globals_t *pMGlobals);
typedef int (*META_ATTACH_FN) (meta_globals_t *pMGlobals);

extern "C" int __declspec( dllexport ) Meta_Detach(void);
typedef int (*META_DETACH_FN) (void);

extern "C" int __declspec( dllexport ) GetExportFunctionsTable(cl_clientfunc_t *pClfuncs);
extern "C" int __declspec( dllexport ) GetExportFunctionsTable_Post(cl_clientfunc_t *pClfuncs);
typedef int (*tGetExportFunctionsTable)(cl_clientfunc_t *pClfuncs);
