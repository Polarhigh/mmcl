#include "stdafx.h"
#include "CRegistry.h"
#include "DebugHelp.h"

CRegistry Registry;
bool CRegistry::Initialised()
{
	return g_bRegisterValid;
}

bool CRegistry::Init(void)
{
	if(g_bRegisterValid)
		return true;
	g_bRegisterValid = RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\Valve\\Half-Life\\Settings\\", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &g_hRegisterKey, NULL) == ERROR_SUCCESS ? true : false;
	return g_bRegisterValid;
}

void CRegistry::Shutdown(void)
{
	if (!g_bRegisterValid)
		return;

	RegCloseKey(g_hRegisterKey);
}

int CRegistry::ReadInt(char *key, int iDefaultValue)
{
	int value;

	if (!g_bRegisterValid)
		return iDefaultValue;

	DWORD type, size = sizeof(DWORD);

	if (RegQueryValueExA(g_hRegisterKey, key, 0, &type, (BYTE *)&value, &size) != ERROR_SUCCESS)
		return iDefaultValue;

//	if (type != iDefaultValue)
//		return iDefaultValue;

	return value;
}

void CRegistry::WriteInt(char *key, int value)
{
	if (g_bRegisterValid)
	{
		auto res=RegSetValueExA(g_hRegisterKey, key, 0, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
		if(res!=ERROR_SUCCESS)
			FatalError("Can't write\n\"%s\" \"%i\"\nto registry.",key,value);
	}
}

char *CRegistry::ReadString(char *key, char *defvalue)
{
	if (!g_bRegisterValid)
		return defvalue;

	DWORD type, size;

	if (RegQueryValueExA(g_hRegisterKey, key, 0, &type, NULL, &size) != ERROR_SUCCESS)
		return defvalue;

	if (type != REG_SZ)
		return defvalue;

	static char value[512];

	if (RegQueryValueExA(g_hRegisterKey, key, 0, &type, (BYTE *)value, &size) != ERROR_SUCCESS)
		return defvalue;

	return value;
}

void CRegistry::WriteString(char *key, char *value)
{
	if (g_bRegisterValid)
	{
		auto res=RegSetValueExA(g_hRegisterKey, key, 0, REG_SZ, (LPBYTE)value, (DWORD)(strlen(value) + 1));
		if(res!=ERROR_SUCCESS)
			FatalError("Can't write\n\"%s\" \"%i\"\nto registry.",key,value);
	}
}