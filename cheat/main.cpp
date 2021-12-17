#include "gui.h"
#include "../Header Files/features/legitbot.h"
#include "../Header Files/features/chams.h"
#include "../Header Files/features/visuals.h"
#include "../Header Files/features/bhop.h"
#include "../Header Files/core/variables.h"
#include "../Header Files/core/includes.h"

void Hook();
void polymorphic();
void Render();

int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{
	polymorphic();
	AllocConsole();
	freopen(XorStr("conin$"), "r", stdin);
	freopen(XorStr("conout$"), "w", stdout);
	freopen(XorStr("conout$"), "w", stderr);

	
	const auto memory = Memory{ XorStr("csgo.exe") };
	const auto client = memory.GetModuleAddress(XorStr("client.dll"));
	const auto engine = memory.GetModuleAddress(XorStr("engine.dll"));

	std::cout << std::hex << XorStr("client.dll -> 0x") << client << std::dec << std::endl;
	std::cout << std::hex << XorStr("engine.dll -> 0x") << engine << std::dec << std::endl;
	if (!client) {
		if (!engine) {
			printf(XorStr("[cheat-menu] Start CSGO / Run as Administrator?"));
			Sleep(-1);
		}
	}
	polymorphic();
	// create gui
	gui::CreateHWindow(XorStr("Cheat Menu"), XorStr("Cheat Menu Class"));
	gui::CreateDevice();
	gui::CreateImGui();
	polymorphic();
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


//
// "Polymorphic Code" rofl
//
void polymorphic() //basic function created by Apxaey that randomly selects a number and writes random assembly instructionss. This is good becuase VAC's main detection method is through known signatures which are just a pattern of bytes. So when we call this function we add assembly and therefore adding random bytes, resulting in a different runtime signature every time the fucntion is called.
{
	std::srand(std::time(0)); //generate random seed from your computers time

	int count = 0;
	for (count; count < 10; count++)
	{
		int index = rand() % (2 - 0 + 1) + 0; //loop through 



		switch (index)
		{

		case 0:

			__asm __volatile
			{
				mov eax, 0
				add bp, ax
				mov eax, 0
				mov ebx, 0
				mov ax, bp
				mov bl, 7
				mul cx
				_emit 0x90


			}



		case 1:

			_asm
			{
				add al, al
				_emit 0x34
				_emit 0x35
				_emit 0x90
				_emit 0x36
				_emit 0x37
				_emit 0x90
				_emit 0x90

			}

		case 2:
			__asm __volatile
			{
			add    eax, 0;
			 dec    ecx;
			 add    eax, 0;
			 inc    ecx;
			 inc    edi;
			 _emit 0xb8
			 dec    ecx
			 inc    ecx;
			 dec    ecx;
			 inc    ecx;
			}


		}

	}
}
