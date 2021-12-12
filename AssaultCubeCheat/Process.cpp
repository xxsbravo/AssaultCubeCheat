#include "stdafx.h"
#include "Process.h"

DWORD GetProcessIdentifier(const wchar_t* process_name)
{
	HANDLE handle_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	DWORD process_identifier = 0;

	if (handle_snapshot != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 process_entry;
		process_entry.dwSize = sizeof(PROCESSENTRY32);

		Process32First(handle_snapshot, &process_entry);
		do
		{
			if (!_wcsicmp(process_entry.szExeFile, process_name))
			{
				process_identifier = process_entry.th32ProcessID;
				break;
			}
		} while (Process32Next(handle_snapshot, &process_entry));
	}
	CloseHandle(handle_snapshot);

	return process_identifier;
}

uintptr_t GetModuleBaseAddress(const wchar_t* module_name, DWORD process_identifier)
{
	HANDLE handle_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, process_identifier);
	uintptr_t base_module_address = 0;

	if (handle_snapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 module_entry;
		module_entry.dwSize = sizeof(MODULEENTRY32);

		Module32First(handle_snapshot, &module_entry);
		do
		{
			if (!_wcsicmp(module_entry.szModule, module_name))
			{
				base_module_address = (uintptr_t)module_entry.modBaseAddr;
				break;
			}
		} while (Module32Next(handle_snapshot, &module_entry));
	}
	CloseHandle(handle_snapshot);

	return base_module_address;
}