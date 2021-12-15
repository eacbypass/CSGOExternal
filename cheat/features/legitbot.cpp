#include "memory.h"

#include "../../Header Files/features/legitbot.h"
#include "../../Header Files/core/variables.h"
#include <thread>
#include <iostream>
#include <winuser.h>
#include "../../Header Files/core/offsets.h"
#include "../../Header Files/core/vector.h"
#include "../../Header Files/core/xorstr.h"

void CLegitBot::Run()
{ 
	if (C::Get<bool>(Vars.bRecoilControlSystem))
		CLegitBot::Get().RecoilControlSystem();
	if (C::Get<bool>(Vars.bTrigger))
		CLegitBot::Get().TriggerBot();
	if (C::Get<bool>(Vars.bAimbot))
		CLegitBot::Get().Aimbot();
}

constexpr Vector3 CalculateAngle(
	const Vector3& localPosition,
	const Vector3& enemyPosition,
	const Vector3& viewAngles) noexcept
{
	return ((enemyPosition - localPosition).ToAngle() - viewAngles);
}

void CLegitBot::Aimbot()
{
	// initialize memory class
	const auto memory = Memory{ XorStr("csgo.exe") };

	// module addresses
	const auto client = memory.GetModuleAddress(XorStr("client.dll"));
	const auto engine = memory.GetModuleAddress(XorStr("engine.dll"));

	std::this_thread::sleep_for(std::chrono::milliseconds(1));

	// aimbot key
	if (!GetAsyncKeyState(C::Get<int>(Vars.bAimbotKey)))
		return;


	// get local player
	const auto& localPlayer = memory.Read<std::uintptr_t>(client + offset::dwLocalPlayer);
	const auto& localTeam = memory.Read<std::int32_t>(localPlayer + offset::m_iTeamNum);

	// eye position = origin + viewOffset
	const auto localEyePosition = memory.Read<Vector3>(localPlayer + offset::m_vecOrigin) +
		memory.Read<Vector3>(localPlayer + offset::m_vecViewOffset);

	const auto& clientState = memory.Read<std::uintptr_t>(engine + offset::dwClientState);

	const auto& viewAngles = memory.Read<Vector3>(clientState + offset::dwClientState_ViewAngles);
	const auto& aimPunch = memory.Read<Vector3>(localPlayer + offset::m_aimPunchAngle) * 2;

	// aimbot fov
	auto bestFov = C::Get<float>(Vars.bAimbotFOV);
	auto bestAngle = Vector3{ };

	for (auto i = 1; i <= 32; ++i)
	{
		const auto& player = memory.Read<std::uintptr_t>(client + offset::dwEntityList + i * 0x10);

		if (memory.Read<std::int32_t>(player + offset::m_iTeamNum) == localTeam)
			continue;

		if (memory.Read<bool>(player + offset::m_bDormant))
			continue;

		if (!memory.Read<std::int32_t>(player + offset::m_iHealth))
			continue;

		if (!memory.Read<bool>(player + offset::m_bSpottedByMask))
			continue;

		const auto boneMatrix = memory.Read<std::uintptr_t>(player + offset::m_dwBoneMatrix);

		// pof of player head in 3d space
		const auto playerHeadPosition = Vector3{
			memory.Read<float>(boneMatrix + 0x30 * 8 + 0x0C),
			memory.Read<float>(boneMatrix + 0x30 * 8 + 0x1C),
			memory.Read<float>(boneMatrix + 0x30 * 8 + 0x2C)
		};

		const auto angle = CalculateAngle(
			localEyePosition,
			playerHeadPosition,
			viewAngles + aimPunch
		);

		const auto fov = std::hypot(angle.x, angle.y);

		if (fov < bestFov)
		{
			bestFov = fov;
			bestAngle = angle;
		}
	}

	// if we have a best angle, do aimbot
	if (!bestAngle.IsZero())
		memory.Write<Vector3>(clientState + offset::dwClientState_ViewAngles, viewAngles + bestAngle / C::Get<float>(Vars.bAimbotSmoothing)); // smoothing
}

struct Vector2
{
	float x = { }, y = { };
};


void CLegitBot::RecoilControlSystem() {
	const auto memory = Memory{ XorStr("csgo.exe") };

	const auto client = memory.GetModuleAddress(XorStr("client.dll"));
	const auto engine = memory.GetModuleAddress(XorStr("engine.dll"));

	auto oldPunch = Vector2{ };

	std::this_thread::sleep_for(std::chrono::milliseconds(1));

	const auto& localPlayer = memory.Read<std::uintptr_t>(client + offset::dwLocalPlayer);
	const auto& shotsFired = memory.Read<std::int32_t>(localPlayer + offset::m_iShotsFired);

	if (shotsFired)
		{
			const auto& clientState = memory.Read<std::uintptr_t>(engine + offset::dwClientState);
			const auto& viewAngles = memory.Read<Vector2>(clientState + offset::dwClientState_ViewAngles);

			const auto& aimPunch = memory.Read<Vector2>(localPlayer + offset::m_aimPunchAngle);

			auto newAngles = Vector2
			{
				viewAngles.x + oldPunch.x - aimPunch.x * 2.f,
				viewAngles.y + oldPunch.y - aimPunch.y * 2.f
			};

			if (newAngles.x > 89.f)
				newAngles.x = 89.f;

			if (newAngles.x < -89.f)
				newAngles.x = -89.f;

			while (newAngles.y > 180.f)
				newAngles.y -= 360.f;

			while (newAngles.y < -180.f)
				newAngles.y += 360.f;

			memory.Write<Vector2>(clientState + offset::dwClientState_ViewAngles, newAngles);

			oldPunch.x = aimPunch.x * 2.f;
			oldPunch.y = aimPunch.y * 2.f;
		}
	else
		{
			oldPunch.x = oldPunch.y = 0.f;
		}
}

void CLegitBot::TriggerBot() {
	const auto memory = Memory{ XorStr("csgo.exe") };
	const auto client = memory.GetModuleAddress(XorStr("client.dll"));

	std::this_thread::sleep_for(std::chrono::milliseconds(1));

	// skip if trigger kry is not down
	if (!GetAsyncKeyState(C::Get<int>(Vars.bTriggerKey)))
		return;

	const auto& localPlayer = memory.Read<std::uintptr_t>(client + offset::dwLocalPlayer);
	const auto& localHealth = memory.Read<std::int32_t>(localPlayer + offset::m_iHealth);

	// skip if local player is dead
	if (!localHealth)
		return;

	const auto& crosshairId = memory.Read<std::int32_t>(localPlayer + offset::m_iCrosshairId);

	if (!crosshairId || crosshairId > 64)
		return;

	const auto& player = memory.Read<std::uintptr_t>(client + offset::dwEntityList + (crosshairId - 1) * 0x10);

	// skip if player is dead
	if (!memory.Read<std::int32_t>(player + offset::m_iHealth))
		return;

	// skip if player is on our team
	if (memory.Read<std::int32_t>(player + offset::m_iTeamNum) ==
		memory.Read<std::int32_t>(localPlayer + offset::m_iTeamNum))
		return;

	std::this_thread::sleep_for(std::chrono::milliseconds(C::Get<int>(Vars.bTriggerDelay)));
	memory.Write<std::uintptr_t>(client + offset::dwForceAttack, 6);
	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	memory.Write<std::uintptr_t>(client + offset::dwForceAttack, 4);
}