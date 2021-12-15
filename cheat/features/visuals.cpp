#include "memory.h"

#include "../../Header Files/features/visuals.h"
#include "../../Header Files/core/variables.h"
#include <thread>
#include <iostream>
#include <winuser.h>
#include "../../Header Files/core/offsets.h"


void CVisuals::Run()
{
	if (C::Get<bool>(Vars.bVisualsFovChanger))
		CVisuals::Get().FovChanger();

}

void CVisuals::FovChanger()
{
	const auto memory = Memory{ XorStr("csgo.exe") };

	

	// module addresses
	const auto client = memory.GetModuleAddress(XorStr("client.dll"));
	const auto engine = memory.GetModuleAddress(XorStr("engine.dll"));

	uintptr_t localPlayer = memory.Read<uintptr_t>(client + offset::dwEntityList);

	memory.Write(localPlayer + offset::m_iDefaultFOV, C::Get<int>(Vars.bVisualsFovChangerAmount));
}