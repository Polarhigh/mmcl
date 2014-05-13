#define MMCL_MAIN
#define _CRT_SECURE_NO_WARNINGS //No time to fix this right way))
#include <Windows.h>

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

#pragma comment (lib, "ws2_32.lib")


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

#include "interface.h"
#include <GameUI\IGameUI.h>
#include <GameUI\IGameConsole.h>
#include <hw\IBaseUI.h>
#include <hw\engine_launcher_api.h>
#include <GameUI\IRunGameEngine.h>
#include <VGUI2\ILocalize.h>
#include <VGUI2\ISystem.h>
#include <VGUI2\IInputinternal.h>
#include <VGUI2\IVGuiV06.h>
#include <VGUI2\IPanel.h>

#include <FileSystem.h>
