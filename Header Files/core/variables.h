#pragma once
#include "cfg.h"

struct tVariables
{
	// Legit Enable
	C_ADD_VARIABLE(bool, bLegitBot, false);

	// Visuals Enable
	C_ADD_VARIABLE(bool, bVisuals, false);
	C_ADD_VARIABLE(bool, bVisualsFovChanger, false);
	C_ADD_VARIABLE(int, bVisualsFovChangerAmount, 90);

	// Triggerbot
	C_ADD_VARIABLE(bool, bTrigger, false);
	C_ADD_VARIABLE(int, bTriggerKey, 0); // @TODO : Add Trigger Key
	C_ADD_VARIABLE(int, bTriggerDelay, 0);

	// Aimbot
	C_ADD_VARIABLE(bool, bAimbot, false);
	C_ADD_VARIABLE(float, bAimbotFOV, 5.0f);
	C_ADD_VARIABLE(float, bAimbotSmoothing, 3.0f);

	// RCS
	C_ADD_VARIABLE(bool, bRecoilControlSystem, false);

	// Chams
	C_ADD_VARIABLE(bool, bChams, false);

	// Bhop
	C_ADD_VARIABLE(bool, bBhop, false);
};

inline tVariables Vars;