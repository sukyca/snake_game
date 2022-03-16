#ifndef DEFINE_H
#define DEFINE_H

#include <windows.h>

extern HANDLE console;
extern COORD CursorPosition;

void gotoxy(int x, int y);

void setcursor(bool visible, DWORD size);

#endif