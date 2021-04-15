#pragma once
#include "Macro.h"
#include "MapDraw.h"
#include "Player.h"

class Play
{
private:
	int m_ix;
	int m_iy;
	int m_iWidth;
	int m_iHeight;
	int m_iTurn;
	bool m_bPlayCheck;

	int m_iMenuSelect;
	int m_iOptSelect;
	MapDraw m_DrawManager;
	Player* P1;
	Player* P2;
public:
	void ShowMenu();
	void ShowOption();
	void GameDraw();
	void UndoMenu();
	void ShowGmaeStatus(Player* P);
	void ReConstruct();
	Play();
	~Play();
};

