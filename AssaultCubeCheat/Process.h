#pragma once

DWORD GetProcessIdentifier(const wchar_t* process_name);
uintptr_t GetModuleBaseAddress(const wchar_t* module_name, DWORD process_identifier);