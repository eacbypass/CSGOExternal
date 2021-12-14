#pragma once
#include "../../cheat/memory/memory.h"
#include "../core/includes.h"
#include <cstdint>
#include <string_view>

class CVisuals : public CSingleton<CVisuals>
{
private:

public:
	// Get
	void Run();
	 
	void FovChanger();
};