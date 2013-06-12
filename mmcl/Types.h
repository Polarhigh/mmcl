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

typedef int (*tInitialize)(cl_enginefunc_t *, int);
typedef void (*tHUD_Init)(void);
typedef int (*tHUD_VidInit)(void);
typedef int (*tHUD_Redraw)(float, int);
typedef int (*tHUD_UpdateClientData)(client_data_t *, float);
typedef void (*tHUD_Reset)(void);
typedef void (*tHUD_PlayerMove)(struct playermove_s *, int);
typedef void (*tHUD_PlayerMoveInit)(struct playermove_s *);
typedef char (*tHUD_PlayerMoveTexture)(char *);
typedef void (*tIN_ActivateMouse)(void);
typedef void (*tIN_DeactivateMouse)(void);
typedef void (*tIN_MouseEvent)(int);
typedef void (*tIN_ClearStates)(void);
typedef void (*tIN_Accumulate)(void);
typedef void (*tCL_CreateMove)(float, struct usercmd_s *, int);
typedef int (*tCL_IsThirdPerson)(void);
typedef void (*tCL_CameraOffset)(float *);
typedef struct kbutton_s *(*tKB_Find)(const char *);
typedef void (*tCAM_Think)(void);
typedef void (*tV_CalcRefdef)(struct ref_params_s *);
typedef int (*tHUD_AddEntity)(int, struct cl_entity_s *, const char *);
typedef void (*tHUD_CreateEntities)(void);
typedef void (*tHUD_DrawNormalTriangles)(void);
typedef void (*tHUD_DrawTransparentTriangles)(void);
typedef void (*tHUD_StudioEvent)(const struct mstudioevent_s *, const struct cl_entity_s *);
typedef void (*tHUD_PostRunCmd)(struct local_state_s *, struct local_state_s *, struct usercmd_s *, int, double, unsigned int);
typedef void (*tHUD_Shutdown)(void);
typedef void (*tHUD_TxferLocalOverrides)(struct entity_state_s *, const struct clientdata_s *);
typedef void (*tHUD_ProcessPlayerState)(struct entity_state_s *, const struct entity_state_s *);
typedef void (*tHUD_TxferPredictionData)(struct entity_state_s *, const struct entity_state_s *, struct clientdata_s *, const struct clientdata_s *, struct weapon_data_s *, const struct weapon_data_s *);
typedef void (*tDemo_ReadBuffer)(int, unsigned char *);
typedef int (*tHUD_ConnectionlessPacket)(struct netadr_s *, const char *, char *, int *);
typedef int (*tHUD_GetHullBounds)(int, float *, float *);
typedef void (*tHUD_Frame)(double time);
typedef int (*tHUD_Key_Event)(int, int, const char *);
typedef void (*tHUD_TempEntUpdate)(double, double, double, struct tempent_s **, struct tempent_s **, int( *Callback_AddVisibleEntity )( struct cl_entity_s *pEntity ), void( *Callback_TempEntPlaySound )( struct tempent_s *pTemp, float damp ));
typedef struct cl_entity_s *(*tHUD_GetUserEntity)(int index);
typedef int (*tHUD_VoiceStatus)(int, qboolean);
typedef void (*tHUD_DirectorMessage)(int, void *);
typedef int (*tHUD_GetStudioModelInterface)(int, struct r_studio_interface_s **, struct engine_studio_api_s *);
