#include "memory.h"

#include "../../Header Files/features/bhop.h"
#include "../../Header Files/core/variables.h"
#include <thread>
#include <iostream>
#include <winuser.h>
#include "../../Header Files/core/offsets.h"



void CBhop::Run()
{
	const auto mem = Memory("csgo.exe");
	const auto client = mem.GetModuleAddress("client.dll");

	const auto localPlayer = mem.Read<std::uintptr_t>(client + offset::dwLocalPlayer);

	const auto localPlayerFlags = mem.Read<std::uintptr_t>(localPlayer + offset::m_fFlags);

	if (GetAsyncKeyState(VK_SPACE))
		(localPlayerFlags & (1 << 0)) ?
		mem.Write<std::uintptr_t>(client + offset::dwForceJump, 6):
		mem.Write<std::uintptr_t>(client + offset::dwForceJump, 4);
}