#include <Windows.h>

int APIENTRY DllMain(HMODULE hDLL, DWORD Reason, LPVOID Reserved)
{
	switch(Reason)
	{
	case DLL_PROCESS_ATTACH:
		MessageBox(0,"Plugin_attach","msg",MB_OK);
		DisableThreadLibraryCalls(hDLL);
		break;
	}

	return TRUE;
}