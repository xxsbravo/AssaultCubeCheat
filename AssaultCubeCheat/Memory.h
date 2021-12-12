#pragma once

#include "stdafx.h"

namespace mem
{
	void Patch(BYTE* source_address, BYTE* destination_address, unsigned int size);
	void Nop(BYTE* destination_address, unsigned int size_of_source);

	uintptr_t FindMultiLevelPointer(uintptr_t pointer, std::vector<uintptr_t>offsets);
	uintptr_t Detour32(BYTE* source_address, BYTE* destination_address, uintptr_t length_of_bytes);
	BYTE* TrampHook32(BYTE* source_address, BYTE* destination_address, uintptr_t length_of_bytes);
};
