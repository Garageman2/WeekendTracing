#pragma once
#include "imgui.h"

inline void StyleMono()
{
    ImGui::GetStyle().FrameRounding = 4.0f;
    ImGui::GetStyle().GrabRounding = 4.0f;
    ImVec4* Colors = ImGui::GetStyle().Colors;
    for(int i = 0; i < 53; i++)
    {
        ImVec4 Base = Colors[i];
        float Val = sqrt((Base.x * Base.x) + (Base.y * Base.y) + (Base.z * Base.z));
         Colors[i] = ImVec4(Val,Val,Val,Base.w);
    }
    return;
}