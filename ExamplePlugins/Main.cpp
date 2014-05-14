#include <Windows.h>

int APIENTRY DllMain(HMODULE hDLL, DWORD Reason, LPVOID Reserved)
{
	switch(Reason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hDLL);
		break;
	}

	return TRUE;
}