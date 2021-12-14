#include "gui.h"
#include "../Header Files/features/legitbot.h"
#include "../Header Files/features/chams.h"
#include "../Header Files/features/visuals.h"
#include "../Header Files/features/bhop.h"
#include "../Header Files/core/variables.h"
#include "../Header Files/core/includes.h"

void Hook();
void Render();

int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);

	
	const auto memory = Memory{ "csgo.exe" };
	const auto client = memory.GetModuleAddress("client.dll");

	std::cout << std::hex << "client.dll -> 0x" << client << std::dec << std::endl;
	if (!client) {
		printf("[cheat-menu] Start CSGO");
		Sleep(-1);
	}
	// create gui
	gui::CreateHWindow("Cheat Menu", "Cheat Menu Class");
	gui::CreateDevice();
	gui::CreateImGui();
	
	while (gui::exit)
	{
		Hook();
		Render();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	// destroy gui
	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

	return EXIT_SUCCESS;
}

void Render() {
	gui::BeginRender();
	gui::Render();
	gui::EndRender();
}
void Hook() {
	if (gui::exit)
	{
		if (C::Get<bool>(Vars.bLegitBot))
			CLegitBot::Get().Run();
		if (C::Get<bool>(Vars.bChams))
			CChams::Get().Run();
		if (C::Get<bool>(Vars.bBhop))
			CBhop::Get().Run();
		if (C::Get<bool>(Vars.bVisuals))
			CVisuals::Get().Run();
	}
}

