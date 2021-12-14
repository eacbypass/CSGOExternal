#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include "../../cheat/memory/memory.h"

#include <cstdint>
#include <string_view>

class CLegitBot : public CSingleton<CLegitBot>
{ 
private:
	// Values
	/* timer for delay before shoot */
	float timerDelay = 0.0f;
public:
	// Get
	void Run();
	// rcs
	void RecoilControlSystem();
	// triggerbot
	void TriggerBot();
	// aimbot
	void Aimbot();
};