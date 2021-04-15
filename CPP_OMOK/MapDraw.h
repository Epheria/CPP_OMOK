#pragma once
#include"Macro.h"
class MapDraw
{
public:
	void BoxDraw(int Start_x, int Start_y, int Width, int Height);
	void DrawPoint(string str, int x, int y);
	void DrawMidText(string str, int x, int y);
	void IntDraw(int iNum, int x, int y);
	void ErasePoint(int x, int y);
	void DrawText(string str, int x, int y);
	int Input(int x, int y);
	string InputName(int x, int y);
	MapDraw();
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~MapDraw();
};
