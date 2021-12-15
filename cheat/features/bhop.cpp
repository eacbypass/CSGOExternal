#include "memory.h"

#include "../../Header Files/features/bhop.h"
#include "../../Header Files/core/variables.h"
#include <thread>
#include <iostream>
#include <winuser.h>
#include "../../Header Files/core/offsets.h"



void CBhop::Run()
{
	const auto mem = Memory(XorStr("csgo.exe"));
	const auto client = mem.GetModuleAddress(XorStr("client.dll"));

	if (GetAsyncKeyState(VK_SPACE))
	{
		DWORD LocPlayer = mem.Read<DWORD>(client + offset::dwLocalPlayer);
		DWORD fFlags = mem.Read<DWORD>(LocPlayer + offset::m_fFlags);

		if (fFlags == 256) //on-air
		{
			mem.Write<int>(client + offset::dwForceJump, 4);
		}
		else
		{
			mem.Write<int>(client + offset::dwForceJump, 5);
		}
	}
}