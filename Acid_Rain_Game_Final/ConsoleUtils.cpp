#include "ConsoleUtils.h"

#include <stdio.h>
#include "Windows.h"
#include <iostream>

void ConsoleUtils::CursorView()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void ConsoleUtils::clear_Screen()
{
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void ConsoleUtils::gotoxy(int x, int y)
{
    printf("\033[%d;%dH", (y), (x));
}