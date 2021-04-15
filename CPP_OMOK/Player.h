#pragma once
#include "Macro.h"
#include "MapDraw.h"



enum DIRECTION
{
	DIRECTION_LEFT = 'a',
	DIRECTION_RIGHT = 'd',
	DIRECTION_UP = 'w',
	DIRECTION_DOWN = 's'
};

enum INPUT_TYPE
{
	INPUT_TYPE_MOVE = 1,
	INPUT_TYPE_DROP = 13,
	INPUT_TYPE_UNDO = 'n',
	INPUT_TYPE_EXIT = 27,
	INPUT_TYPE_OPTION = 'p'
};

typedef struct Stone
{
	int m_iStonex = 0;
	int m_iStoney = 0;
}Stone;

class Player
{
private:
	MapDraw m_DrawManager;
	string m_strShape;
	string m_strName;
	string m_strStone;

	vector<Stone> PlayerStone;
	int m_ix;
	int m_iy;
	int m_iWidth;
	int m_iHeight;
	int m_iInitx;
	int m_iInity;
	int m_iUndoCount;
	int m_iWinCount;
	int m_iStoneCount;
	int m_iTurn;
	bool m_bSaved;
	bool m_bGameover;
	bool m_bWin;
public:
	void Draw();
	int Move(int x, int y, int Width, int Height, int iTurn, Player* Enemy);
	void DrawStone();
	void DrawStone(int x, int y);
	void CreateStone();
	void EraseStone();
	void ReDrawStone();
	void ReDrawMap(int Width, int Height);
	void ReDrawMap(int x, int y, int Width, int Height);
	void SetWidthHeight(int Width, int Height)
	{
		m_iWidth = Width;
		m_iHeight = Height;
		m_ix = (m_iWidth) * 0.5f;
		if (m_ix % 2 == 1)
			m_ix++;
		m_iy = (m_iHeight * 0.5f);
	}
	void ClearStone();
	bool DirectionCheck(int x, int y);
	void CheckWinner(int x, int y);
	bool ReturnWinner();
	bool CheckPos(int x, int y);
	void SaveInfo(Player* Enemy);
	void SaveReplay(Player* Enemy);
	void LoadInfo(Player* Enemy);
	void LoadReplay(Player* Enemy);
	void InitFile()
	{
		ofstream init;
		init.open("Player.txt");
		init.close();
	}
	void InitReplay()
	{
		ofstream init;
		init.open("Replay.txt");
		init.close();
	}
	void SetStone(string strStone)
	{
		m_strStone = strStone;
	}
	void SetShape(string strShape)
	{
		m_strShape = strShape;
	}
	void SetTurn(int iTurn)
	{
		m_iTurn = iTurn;
	}
	inline int GetTurn()
	{
		return m_iTurn;
	}
	inline void SetName(string strName)
	{
		m_strName = strName;
	}
	inline string GetName()
	{
		return m_strName;
	}
	inline void SetUndoCount(int iUndoCount)
	{
		m_iUndoCount = iUndoCount;
	}
	inline int GetUndoCount()
	{
		return m_iUndoCount;
	}
	inline bool GetCheckSaved()
	{
		ifstream m_fLoad;
		m_fLoad.open("Player.txt");
		if (m_fLoad.is_open())
		{
			int check;
			m_fLoad >> check;
			if (check > 0)
				m_bSaved = true;
			else
				m_bSaved = false;
		}
		return m_bSaved;
	}
	inline bool GetCheckSavedReplay()
	{
		ifstream m_fLoad;
		m_fLoad.open("Replay.txt");
		if (m_fLoad.is_open())
		{
			int check;
			m_fLoad >> check;
			if (check > 0)
				m_bSaved = true;
			else
				m_bSaved = false;
		}
		return m_bSaved;
	}
	inline bool GetGameover()
	{
		return m_bGameover;
	}
	inline int GetStoneCount()
	{
		return m_iStoneCount;
	}
	inline bool GetWin()
	{
		return m_bWin;
	}
	void InitWinCount()
	{
		m_iWinCount = 0;
	}
	void InitPos()
	{
		m_ix = m_iInitx;
		m_iy = m_iInity;
	}

	Player(int x, int y);
	~Player();
};

