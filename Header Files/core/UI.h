#pragma once
//#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS
#include "../../imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
//#define IMGUI_DEFINE_PLACEMENT_NEW
#include "../../imgui/imgui_internal.h"
//#include "imgui/directx9/imgui_impl_dx9.h"
#include <Windows.h>
#include <string>
#include <functional>
#include <vector>

namespace ImGui {
	bool Hotkey(const char* label, int* k, const ImVec2& size_arg = ImVec2(0, 0));
}