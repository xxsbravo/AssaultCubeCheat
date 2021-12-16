#include "stdafx.h"
#include "Hook.h"

typedef BOOL(__stdcall* twglSwapBuffers)(HDC hDc);
twglSwapBuffers owglSwapBuffers;

bool bHealth = false, bArmor = false, bAmmo = false,
bRecoil = false, bGhost = false, bBlink = false;

DWORD process_identifier = GetProcessIdentifier(L"ac_client.exe");
uintptr_t base_module_address = GetModuleBaseAddress(L"ac_client.exe", process_identifier);
uintptr_t* local_player_pointer = (uintptr_t*)(base_module_address + 0x187C0C);

BOOL __stdcall hkwglSwapBuffers(HDC hDc)
{
	if (GetAsyncKeyState(VK_NUMPAD1) & 1)
	{
		bHealth = !bHealth;

		if (bHealth)
		{
			int health = (*local_player_pointer + 0xEC);
			*(int*)health = 1337;
		}
	}

	if (GetAsyncKeyState(VK_NUMPAD2) & 1)
	{
		bArmor = !bArmor;

		if (bArmor)
		{
			int armor = (*local_player_pointer + 0xF0);
			*(int*)armor = 1337;
		}
	}

	if (GetAsyncKeyState(VK_NUMPAD3) & 1)
	{
		bAmmo = !bAmmo;

		if (bAmmo)
		{
			uintptr_t ammoAddr = mem::FindMultiLevelPointer((uintptr_t)local_player_pointer, { 0x368, 0x14, 0x0 });
			int* ammo = (int*)(ammoAddr);
			*(ammo) = 1337;
		}
	}

	if (GetAsyncKeyState(VK_NUMPAD4) & 1)
	{
		bRecoil = !bRecoil;

		if (bRecoil)
		{

		}
	}

	if (GetAsyncKeyState(VK_NUMPAD5) & 1)
	{
		bGhost = !bGhost;

		if (bGhost)
		{
			BYTE* ghostMode = (BYTE*)(*local_player_pointer + 0x76);
			BYTE* flyMode = (BYTE*)(*local_player_pointer + 0x318);
			*ghostMode = 6;
			*flyMode = 5;
		}
		else
		{
			BYTE* ghostMode = (BYTE*)(*local_player_pointer + 0x76);
			BYTE* flyMode = (BYTE*)(*local_player_pointer + 0x318);
			*ghostMode = 0;
			*flyMode = 0;
		}
	}

	if (GetAsyncKeyState(0x43) & 1)
	{
		bBlink = !bBlink;

		if (bBlink)
		{
			BYTE* blink = (BYTE*)(*local_player_pointer + 0x74);
			*blink = 100;

		}
		else
		{
			BYTE* blink = (BYTE*)(*local_player_pointer + 0x74);
			*blink = 0;
		}
	}

	return owglSwapBuffers(hDc);
}

Hook::Hook()
{
	Hook::ExecuteHook();
}

Hook::~Hook()
{
	Hook::CleanupHook();
}

BOOL Hook::ExecuteHook()
{
	owglSwapBuffers = (twglSwapBuffers)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers");
	owglSwapBuffers = (twglSwapBuffers)mem::TrampHook32((BYTE*)owglSwapBuffers, (BYTE*)hkwglSwapBuffers, 5);

	return FALSE;
}

// Cleans or reverts all stolen and altered memory
BOOL Hook::CleanupHook()
{
	return FALSE;
}