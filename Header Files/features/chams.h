#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include "../../cheat/memory/memory.h"
#include "../core/includes.h"

#include <cstdint>
#include <string_view>

class CChams : public CSingleton<CChams>
{
private:

public:
	// Get
	void Run();
};