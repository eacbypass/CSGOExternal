#include <iostream>

namespace offset
{
	// client

	constexpr ::std::ptrdiff_t dwLocalPlayer = 0xDB458C; // updated 12/13/2021
	constexpr ::std::ptrdiff_t dwEntityList = 0x4DCFA94; // updated 12/15/2021
	constexpr ::std::ptrdiff_t dwForceAttack = 0x31FFF74; // updated 12/13/2021
	constexpr ::std::ptrdiff_t dwForceJump = 0x527995C; // updated 12/13/2021 
	constexpr ::std::ptrdiff_t dwClientState = 0x589FC4; // updated 12/13/2021
	constexpr ::std::ptrdiff_t dwClientState_ViewAngles = 0x4D90; // updated 12/13/2021

	// engine
	constexpr ::std::uintptr_t model_ambient_min = 0x58D03C; // updated 12/13/2021

	// entity
	constexpr ::std::ptrdiff_t m_iHealth = 0x100; // updated 12/13/2021
	constexpr ::std::ptrdiff_t m_iTeamNum = 0xF4; // updated 12/13/2021
	constexpr ::std::ptrdiff_t m_iCrosshairId = 0x11838; // updated 12/13/2021
	constexpr ::std::ptrdiff_t m_clrRender = 0x70; // updated 12/13/2021
	constexpr ::std::ptrdiff_t m_fFlags = 0x104; // updated 12/13/2021
	constexpr ::std::ptrdiff_t m_aimPunchAngle = 0x303C; // updated 12/13/2021
	constexpr ::std::ptrdiff_t m_iShotsFired = 0x103E0; // updated 12/13/2021
	constexpr ::std::ptrdiff_t m_dwBoneMatrix = 0x26A8; // updated 12/13/2021
	constexpr ::std::ptrdiff_t m_bDormant = 0xED; // updated 12/13/2021
	constexpr ::std::ptrdiff_t m_vecOrigin = 0x138; // updated 12/13/2021
	constexpr ::std::ptrdiff_t m_vecViewOffset = 0x108; // updated 12/13/2021
	constexpr ::std::ptrdiff_t m_bSpottedByMask = 0x980; // updated 12/13/2021

	// netvars
	constexpr ::std::ptrdiff_t m_iDefaultFOV = 0x333C; // updated 12/13/2021

}

