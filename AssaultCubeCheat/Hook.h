#pragma once
#include "stdafx.h"
#include "Process.h"
#include "Memory.h"

struct Hook
{
public:
	Hook();
	~Hook();
private:
	BOOL ExecuteHook();
	BOOL CleanupHook();
};