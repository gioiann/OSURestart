#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <tchar.h>

int main()
{
	SetConsoleTitle(TEXT("OSU! Restart"));
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD prevMode;
	GetConsoleMode(hIn, &prevMode);
	SetConsoleMode(hIn, (prevMode | ENABLE_EXTENDED_FLAGS) & ~ENABLE_QUICK_EDIT_MODE);
	SMALL_RECT smallRect;
	smallRect.Left = 0;
	smallRect.Top = 0;
	smallRect.Right = 0;
	smallRect.Bottom = 0;
	SetConsoleWindowInfo(hOut, TRUE, &smallRect);
	COORD coord;
	coord.X = 30;
	coord.Y = 5;
	SetConsoleScreenBufferSize(hOut, coord);
	smallRect.Left = 0;
	smallRect.Top = 0;
	smallRect.Right = 29;
	smallRect.Bottom = 4;
	SetConsoleWindowInfo(hOut, TRUE, &smallRect);
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(hOut, coord);
	Sleep(50);
	ShowWindow(GetConsoleWindow(), SW_MINIMIZE);

	INPUT keydown[1] = {};
	ZeroMemory(keydown, sizeof(keydown));
	keydown[0].type = INPUT_KEYBOARD;
	keydown[0].ki.wVk = VK_CONTROL;
	keydown[0].ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
	INPUT keyup[1] = {};
	ZeroMemory(keyup, sizeof(keyup));
	keyup[0].type = INPUT_KEYBOARD;
	keyup[0].ki.wVk = VK_CONTROL;
	keyup[0].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_EXTENDEDKEY;
	int waitCyclesKeyDown = 20;
	const int waitCyclesKeyUp = -25;
	bool isKeyDown = false;
	while (1) {
		if ((GetKeyState(VK_LEFT) & 0x8000) && (GetKeyState(VK_DOWN) & 0x8000))
		{
			if (waitCyclesKeyDown <= 0) {
				if (isKeyDown == false) {
					isKeyDown = true;
					SendInput(1, keydown, sizeof(INPUT));
				} else if (waitCyclesKeyDown <= waitCyclesKeyUp) {
					isKeyDown = false;
					SendInput(1, keyup, sizeof(INPUT));
					waitCyclesKeyDown = 10;
					continue;
				}
			}
			waitCyclesKeyDown--;
			Sleep(10);
			continue;
		}

		if (isKeyDown == true) {
			isKeyDown = false;
			SendInput(1, keyup, sizeof(INPUT));
		}
		waitCyclesKeyDown = 20;
		Sleep(50);
	}
}
