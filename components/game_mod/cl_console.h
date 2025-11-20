#pragma once

static field_t *g_consoleField = (field_t *)0x00C72280;


struct ConDrawInputGlob
{
	char autoCompleteChoice[64];
	int matchIndex;
	int matchCount;
	const char* inputText;
	int inputTextLen;
	bool hasExactMatch;
	bool mayAutoComplete;
	float x;
	float y;
	float leftX;
	float fontHeight;
};

static ConDrawInputGlob* conDrawInputGlob = (ConDrawInputGlob*)0xC48A08;

VANILLA_FUNC(Con_Close, void (__cdecl*)(int localClientNum), 0x004B8020);

void Con_ToggleConsole();
bool Con_HasActiveAutoComplete();
bool Con_CancelAutoComplete();
void Con_ImproveConsoleInfo();