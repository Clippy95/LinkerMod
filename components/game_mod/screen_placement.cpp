#include "stdafx.h"



uintptr_t ScrPlace_CalcSafeAreaOffsets_ogaddr;

void __declspec(naked) ScrPlace_CalcSafeAreaOffsets_hk()
{
    __asm
    {

        push eax
        mov eax, [safeArea_horizontal]
        mov eax, [eax].current.value
        mov dword ptr[esp + 0x1C + 4], eax

        mov eax, [safeArea_vertical]
        mov eax, [eax].current.value
        mov dword ptr[esp + 0x1C + 4 + 4], eax


        pop eax
        jmp ScrPlace_CalcSafeAreaOffsets_ogaddr
    }
}

void Patch_ScreenPlacement() {


    ScrPlace_CalcSafeAreaOffsets_ogaddr = (uintptr_t)Detours::X86::DetourFunction(
        (PBYTE)0x7A1C90,
        (PBYTE)&ScrPlace_CalcSafeAreaOffsets_hk
    );
}