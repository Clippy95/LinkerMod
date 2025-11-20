#include "stdafx.h"

// /client/cl_console.cpp:289
void Con_ToggleConsole()
{
	Field_Clear(g_consoleField);
	Con_CancelAutoComplete();

	g_consoleField->widthInPixels = 620;
	g_consoleField->charHeight = 16.0f;
	g_consoleField->fixedSize = true;

	*(bool *)0xC6924C = false;
	*(DWORD *)0x2910160 ^= 1;
}

// /client/cl_console.cpp:2568
bool Con_HasActiveAutoComplete()
{
	// return conDrawInputGlob.matchIndex >= 0 && conDrawInputGlob.autoCompleteChoice[0];
	return (*(int *)0xC48A48 >= 0 && ((BYTE *)0xC48A08)[0]);
}

// /client/cl_console.cpp:2599
bool Con_CancelAutoComplete()
{
	if (Con_HasActiveAutoComplete())
	{
		*(int *)0xC48A48 = -1;		// conDrawInputGlob.matchIndex
		((BYTE *)0xC48A08)[0] = 0;	// conDrawInputGlob.autoCompleteChoice[0]

		return true;
	}

	return false;
}

float whiteColor[] = {8.0f, 8.0f, 8.0f, 1.0f};

void __cdecl R_AddCmdDrawText_drawDvarFlags(dvar_s* dvar, uintptr_t return_address, const char* text, int maxChars, Font_s* font, float x, float y, float xScale, float yScale, float rotation, const float* color, int style) {

	R_AddCmdDrawText(text, maxChars, font, x, y, xScale, yScale, rotation, color, style);

	auto flags = dvar->flags;
	// from T4M
	const char* flagsString = va("Flags: %s%s%s%s%s%s%s%s%s%s%s%s%s%s",
		(flags & DVAR_ARCHIVE ? "Archive, " : ""),
		(flags & DVAR_USERINFO ? "UserInfo, " : ""),
		(flags & DVAR_SERVERINFO ? "ServerInfo, " : ""),
		(flags & DVAR_SYSTEMINFO ? "SystemInfo, " : ""),
		(flags & DVAR_INIT ? "Init, " : ""),
		(flags & DVAR_LATCH ? "Latch, " : ""),
		(flags & DVAR_ROM ? "Rom, " : ""),
		(flags & DVAR_CHEAT ? "Cheat, " : ""),
		(flags & DVAR_DEVELOPER ? "Developer, " : ""),
		(flags & DVAR_SAVED ? "Saved, " : ""),
		(flags & DVAR_NORESTART ? "NoRestart, " : ""),
		(flags & DVAR_CHANGEABLE_RESET ? "ChangeableReset, " : ""),
		(flags & DVAR_EXTERNAL ? "External, " : ""),
		(flags & DVAR_AUTOEXEC ? "AutoExec" : ""));

	conDrawInputGlob->y = conDrawInputGlob->fontHeight + (float)(conDrawInputGlob->fontHeight + conDrawInputGlob->y);
	conDrawInputGlob->x = conDrawInputGlob->leftX;

	R_AddCmdDrawText(flagsString, 40, font, conDrawInputGlob->x, conDrawInputGlob->y, xScale, yScale, rotation, whiteColor, style);

}

void __declspec(naked) R_AddCmdDrawText_hk()
{
	__asm
	{

		push edi
		call R_AddCmdDrawText_drawDvarFlags
		pop edi
		retn
	}
}


void Con_ImproveConsoleInfo() {

	PatchCall(0x79D2BD, (PBYTE)&R_AddCmdDrawText_hk);
	PatchMemory(0x0079D083, (PBYTE)"\x03", 1);

}