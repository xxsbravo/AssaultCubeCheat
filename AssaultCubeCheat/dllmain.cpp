#include "stdafx.h"
#include "Hook.h"

class Hack
{
private:
	FILE* file;
	Hook* hook;

	void CreateConsole(FILE* f)
	{
		AllocConsole();
		freopen_s(&f, "CONOUT$", "w", stdout);
	}

	FILE* PrintHackInterface(FILE* f)
	{
		CreateConsole(f);

		std::cout << "------------------------------ASSAULT CUBE HACK------------------------------" << std::endl;
		std::cout << "Press Numpad [1]: Health Hack" << std::endl;
		std::cout << "Press Numpad [2]: Armor Hack" << std::endl;
		std::cout << "Press Numpad [3]: Ammo Hack" << std::endl;
		std::cout << "Press Numpad [4]: Recoil Hack" << std::endl;
		std::cout << "Press Numpad [5]: Ghost Hack" << std::endl;
		std::cout << "Press ['c']: Blink/End Blink" << std::endl;

		return f;
	}

public:
	Hack()
	{
		file = PrintHackInterface(file);
		hook = new Hook();
	}

	~Hack()
	{
		delete hook;
	}
};

BOOL WINAPI LaunchHack()
{
	Hack* hack = new Hack();

	return 0;
}

BOOL APIENTRY DllMain(HMODULE module_handle, DWORD reason_for_call, LPVOID behavior)
{
	switch (reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)LaunchHack, module_handle, 0, nullptr));
	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}

	return TRUE;
}