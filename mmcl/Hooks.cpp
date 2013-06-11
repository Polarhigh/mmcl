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

#include <Windows.h>
#include "Hooks.h"

void RedirectFunction(hook *pHook, LPVOID oldFunctionAddr, LPVOID newFunction)
{
	pHook->pAddress = oldFunctionAddr;
    BYTE tempJMP[SIZE] = {0xE9, 0x90, 0x90, 0x90, 0x90};
    memcpy(pHook->newJMP, tempJMP, SIZE);
    DWORD JMPSize = ((DWORD)newFunction - (DWORD)oldFunctionAddr - 5);
	DWORD oldProtect = NULL;
    VirtualProtect((LPVOID)oldFunctionAddr, SIZE, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(pHook->oldJMP, oldFunctionAddr, SIZE);
    memcpy(&pHook->newJMP[1], &JMPSize, 4);
    memcpy(oldFunctionAddr, pHook->newJMP, SIZE);
    VirtualProtect((LPVOID)oldFunctionAddr, SIZE, oldProtect, NULL);
}

void DisableRedirect(hook *pHook)
{
	DWORD oldProtect = NULL;
    VirtualProtect((LPVOID)pHook->pAddress, SIZE, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(pHook->pAddress, pHook->oldJMP, SIZE);
	VirtualProtect((LPVOID)pHook->pAddress, SIZE, oldProtect, NULL);
}

void EnableRedirect(hook *pHook)
{
	DWORD oldProtect = NULL;
    VirtualProtect((LPVOID)pHook->pAddress, SIZE, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(pHook->pAddress, pHook->newJMP, SIZE);
	VirtualProtect((LPVOID)pHook->pAddress, SIZE, oldProtect, NULL);
}