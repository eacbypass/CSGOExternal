#include "memory.h"

#include "../../Header Files/features/chams.h"
#include "../../Header Files/core/variables.h"
#include <thread>
#include <iostream>
#include <winuser.h>
#include "../../Header Files/core/offsets.h"

struct Color
{
	std::uint8_t r{ }, g{ }, b{ };
};

void CChams::Run()
{
	const auto memory = Memory{ XorStr("csgo.exe") };

	// module addresses
	const auto client = memory.GetModuleAddress(XorStr("client.dll"));
	const auto engine = memory.GetModuleAddress(XorStr("engine.dll"));

	constexpr const auto teamColor = Color{ 0, 0, 255 }; // @TODO: Make changable in menu
	constexpr const auto enemyColor = Color{ 255, 0, 0 }; // @TODO: Make changable in menu

	const auto& localPlayer = memory.Read<std::uintptr_t>(client + offset::dwLocalPlayer);
	const auto& localTeam = memory.Read<std::int32_t>(localPlayer + offset::m_iTeamNum);

	for (auto i = 1; i <= 32; ++i)
	{
		const auto& entity = memory.Read<std::uintptr_t>(client + offset::dwEntityList + i * 0x10);

		if (memory.Read<std::int32_t>(entity + offset::m_iTeamNum) == localTeam)
		{
			memory.Write<Color>(entity + offset::m_clrRender, teamColor);
		}
		else
		{
			memory.Write<Color>(entity + offset::m_clrRender, enemyColor);
		}

		//Model Brightness
		//float brightness = 0.f;
		//const auto _this = static_cast<std::uintptr_t>(engine + offset::model_ambient_min - 0x2c);
		//memory.Write<std::int32_t>(engine + offset::model_ambient_min, *reinterpret_cast<std::uintptr_t*>(&brightness) ^ _this);
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(1));
}