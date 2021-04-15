#include "Player.h"

Player::Player(int x, int y)
{
	m_ix = x;
	if (m_ix % 2 == 1)
		m_ix++;
	m_iy = y;
	m_iUndoCount = 4;
	m_iWinCount = 0;
	m_iInitx = m_ix;
	m_iInity = m_iy;
	m_iStoneCount = 0;
	m_bSaved = false;
	m_bWin = false;
}

int Player::Move(int x, int y, int Width, int Height, int iTurn, Player* Enemy)
{
	char ch = _getch();

	if (CheckPos(m_ix, m_iy) == false && Enemy->CheckPos(m_ix, m_iy) == false)
	{
		m_DrawManager.ErasePoint(m_ix, m_iy);
		ReDrawMap(Width, Height);
	}

	switch (ch)
	{
	case DIRECTION_LEFT:
		if (m_ix * 2 > x + 1)
			m_ix--;
		break;

	case DIRECTION_RIGHT:
		if (m_ix * 2 < x + Width * 2 - 2)
			m_ix++;
		break;

	case DIRECTION_UP:
		if (m_iy > y)
			m_iy--;
		break;

	case DIRECTION_DOWN:
		if (m_iy < y + Height - 1)
			m_iy++;
		break;

	case INPUT_TYPE_UNDO:
		return INPUT_TYPE_UNDO;

	case INPUT_TYPE_DROP:
		if (CheckPos(m_ix, m_iy) == true)
			break;
		else if (Enemy->CheckPos(m_ix, m_iy) == true)
			break;

		return INPUT_TYPE_DROP;

	case INPUT_TYPE_OPTION:
		return INPUT_TYPE_OPTION;

	case INPUT_TYPE_EXIT:
		//Enemy->PlayerStone.clear();
		//PlayerStone.clear();
		return INPUT_TYPE_EXIT;
	}

	if (CheckPos(m_ix, m_iy) == true)
		DrawStone();
	else if (Enemy->CheckPos(m_ix, m_iy) == true)
		Enemy->DrawStone(m_ix, m_iy);
	else
	{
		Draw();
	}
	return INPUT_TYPE_MOVE;
}

void Player::Draw()
{
	m_DrawManager.DrawPoint(m_strShape, m_ix, m_iy);
}

void Player::CreateStone()
{
	Stone tmp;
	tmp.m_iStonex = m_ix;
	tmp.m_iStoney = m_iy;
	PlayerStone.push_back(tmp);
	m_iStoneCount++;
}

void Player::DrawStone()
{
	m_DrawManager.DrawPoint(m_strStone, m_ix, m_iy);
}
void Player::DrawStone(int x, int y)
{
	m_DrawManager.DrawPoint(m_strStone, x, y);
}

void Player::ReDrawStone()
{

	for (vector<Stone>::iterator iter = PlayerStone.begin(); iter != PlayerStone.end(); iter++)
		m_DrawManager.DrawPoint(m_strStone, iter->m_iStonex, iter->m_iStoney);
}

void Player::EraseStone()
{
	for (vector<Stone>::iterator iter = PlayerStone.begin(); iter != PlayerStone.end(); iter++)
	{
		if (iter == PlayerStone.end() - 1)
		{
			m_DrawManager.ErasePoint(iter->m_iStonex, iter->m_iStoney);
			ReDrawMap(iter->m_iStonex, iter->m_iStoney, m_iWidth, m_iHeight);
			break;
		}
	}

	if (PlayerStone.empty())
		return;
	m_iStoneCount--;
	PlayerStone.pop_back();
}

bool Player::CheckPos(int x, int y)
{
	for (vector<Stone>::iterator iter = PlayerStone.begin(); iter != PlayerStone.end(); iter++)
		if (iter->m_iStonex == x && iter->m_iStoney == y)
			return true;
	return false;
}

void Player::ClearStone()
{
	PlayerStone.clear();
}

void Player::ReDrawMap(int Width, int Height)
{
	if (m_ix == 0 && m_iy == 0)
		m_DrawManager.DrawPoint("¦£", m_ix, m_iy);
	else if (m_ix == Width - 1 && m_iy == Height - 1)
		m_DrawManager.DrawPoint("¦¥", Width - 1, Height - 1);
	else if (m_ix == 0 && m_iy == Height - 1)
		m_DrawManager.DrawPoint("¦¦", m_ix, Height - 1);
	else if (m_ix == Width - 1 && m_iy == 0)
		m_DrawManager.DrawPoint("¦¤", Width - 1, m_iy);
	else if (m_iy == 0 && m_ix != 0 && m_ix != Width - 1)
	{
		m_DrawManager.DrawPoint("¦¨", m_ix, m_iy);
	}
	else if (m_iy == Height - 1 && m_ix != Width - 1 && m_ix != 0)
	{
		m_DrawManager.DrawPoint("¦ª", m_ix, m_iy);
	}
	else if (m_ix == 0 && m_iy != 0 && m_iy != Height - 1)
	{
		m_DrawManager.DrawPoint("¦§", m_ix, m_iy);
	}
	else if (m_ix == Width - 1 && m_iy != Height - 1 && m_iy != 0)
	{
		m_DrawManager.DrawPoint("¦©", m_ix, m_iy);
	}
	else
		m_DrawManager.DrawPoint("¦«", m_ix, m_iy);
}

void Player::ReDrawMap(int x, int y, int Width, int Height)
{
	if (x == 0 && y == 0)
		m_DrawManager.DrawPoint("¦£", x, y);
	else if (x == Width - 1 && y == Height - 1)
		m_DrawManager.DrawPoint("¦¥", Width - 1, Height - 1);
	else if (x == 0 && y == Height - 1)
		m_DrawManager.DrawPoint("¦¦", x, Height - 1);
	else if (x == Width - 1 && y == 0)
		m_DrawManager.DrawPoint("¦¤", Width - 1, y);
	else if (y == 0)
	{
		m_DrawManager.DrawPoint("¦¨", x, y);
	}
	else if (y == Height - 1)
	{
		m_DrawManager.DrawPoint("¦ª", x, y);
	}
	else if (x == 0)
	{
		m_DrawManager.DrawPoint("¦§", x, y);
	}
	else if (x == Width - 1)
	{
		m_DrawManager.DrawPoint("¦©", x, y);
	}
	else
		m_DrawManager.DrawPoint("¦«", x, y);
}


void Player::CheckWinner(int x, int y)
{
	for (int tempx = m_ix, tempy = m_iy; CheckPos(tempx, tempy) == true; tempx += x, tempy += y)
	{
		m_iWinCount++;
	}
}


bool Player::DirectionCheck(int x, int y)
{

	CheckWinner(x, y);
	CheckWinner(x * -1, y * -1);
	if (m_iWinCount == 6)
	{
		m_iWinCount = 0;
		return true;
	}
	else
	{
		m_iWinCount = 0;
		return false;
	}
}

bool Player::ReturnWinner()
{
	if (DirectionCheck(1, 0))
		return true;
	else if (DirectionCheck(0, 1))
		return true;
	else if (DirectionCheck(1, 1))
		return true;
	else if (DirectionCheck(-1, 1))
		return true;
	else
		return false;
}

void Player::SaveInfo(Player* Enemy)
{
	ofstream m_fSave;
	Stone tmp;
	int j = 0;

	m_fSave.open("Player.txt");
	if (m_fSave.is_open())
	{
		m_fSave << m_iTurn << endl;
		m_fSave << m_iStoneCount << endl;
		m_fSave << Enemy->m_iStoneCount << endl;
		m_fSave << m_strShape << " " << m_strStone << " " << m_strName << endl;
		m_fSave << m_iWidth << " " << m_iHeight << " " << m_iUndoCount << endl;
		m_fSave << Enemy->m_strShape << " " << Enemy->m_strStone << " " << Enemy->m_strName << endl;
		m_fSave << Enemy->m_iWidth << " " << Enemy->m_iHeight << " " <<
			Enemy->m_iUndoCount << endl;

		if (m_iStoneCount > Enemy->m_iStoneCount)
			m_fSave << 1 << " " << 0 << endl;
		else
			m_fSave << 0 << " " << 1 << endl;

		for (vector<Stone>::iterator iter = PlayerStone.begin(); iter != PlayerStone.end(); iter++)
			m_fSave << iter->m_iStonex << " " << iter->m_iStoney << endl;

		for (vector<Stone>::iterator iter = Enemy->PlayerStone.begin(); iter != Enemy->PlayerStone.end(); iter++)
			m_fSave << iter->m_iStonex << " " << iter->m_iStoney << endl;

		m_bSaved = true;
		Enemy->m_bSaved = true;
	}
	m_fSave.close();
}

void Player::LoadInfo(Player* Enemy)
{
	int x, y;
	ifstream m_fLoad;
	Stone tmp;

	m_fLoad.open("Player.txt");
	if (m_fLoad.is_open())
	{
		m_fLoad >> m_iTurn;
		m_fLoad >> m_iStoneCount;
		m_fLoad >> Enemy->m_iStoneCount;

		if (m_iStoneCount > Enemy->m_iStoneCount)
		{
			m_fLoad >> Enemy->m_strShape >> Enemy->m_strStone >> Enemy->m_strName;
			m_fLoad >> Enemy->m_iWidth >> Enemy->m_iHeight >> Enemy->m_iUndoCount;
			m_fLoad >> m_strShape >> m_strStone >> m_strName;
			m_fLoad >> m_iWidth >> m_iHeight >> m_iUndoCount;

		}
		else
		{
			m_fLoad >> m_strShape >> m_strStone >> m_strName;
			m_fLoad >> m_iWidth >> m_iHeight >> m_iUndoCount;
			m_fLoad >> Enemy->m_strShape >> Enemy->m_strStone >> Enemy->m_strName;
			m_fLoad >> Enemy->m_iWidth >> Enemy->m_iHeight >> Enemy->m_iUndoCount;
		}

		m_fLoad >> x >> y;
		if (x == 0)
		{
			for (int i = 0; i < m_iStoneCount; i++)
			{
				m_fLoad >> tmp.m_iStonex >> tmp.m_iStoney;
				PlayerStone.push_back(tmp);
			}
			for (int i = 0; i < Enemy->m_iStoneCount; i++)
			{
				m_fLoad >> tmp.m_iStonex >> tmp.m_iStoney;
				Enemy->PlayerStone.push_back(tmp);
			}
			Enemy->m_bWin = true;
		}
		else
		{
			for (int i = 0; i < m_iStoneCount; i++)
			{
				m_fLoad >> tmp.m_iStonex >> tmp.m_iStoney;
				PlayerStone.push_back(tmp);
			}
			for (int i = 0; i < Enemy->m_iStoneCount; i++)
			{
				m_fLoad >> tmp.m_iStonex >> tmp.m_iStoney;
				Enemy->PlayerStone.push_back(tmp);
			}
			m_bWin = true;
		}
	}
	m_fLoad.close();
}

void Player::SaveReplay(Player* Enemy)
{
	ofstream m_fSave;
	Stone tmp;
	int j = 0;
	m_bGameover = true;
	m_fSave.open("Replay.txt");
	if (m_fSave.is_open())
	{
		m_fSave << 1 << " " << Enemy->m_strStone << " " << m_strStone << " " << Enemy->m_iStoneCount << endl;
		m_fSave << Enemy->m_strName << " " << m_strName << endl;
		if (m_iStoneCount > Enemy->m_iStoneCount)
		{
			m_fSave << 1 << " " << 0 << endl;
			for (int i = 0; i < m_iStoneCount; i++)
			{
				m_fSave << PlayerStone.at(i).m_iStonex << " " << PlayerStone.at(i).m_iStoney << endl;
				if (j < m_iStoneCount - 1)
					m_fSave << Enemy->PlayerStone.at(j).m_iStonex << " " << Enemy->PlayerStone.at(j).m_iStoney << endl;
				j++;
			}
		}
		else
		{
			m_fSave << 0 << " " << 1 << endl;

			for (int i = 0; i < m_iStoneCount; i++)
			{
				m_fSave << endl << Enemy->PlayerStone.at(i).m_iStonex << " " << Enemy->PlayerStone.at(i).m_iStoney << endl;
				m_fSave << PlayerStone.at(i).m_iStonex << " " << PlayerStone.at(i).m_iStoney;
			}
		}
	}
	m_fSave.close();
}

void Player::LoadReplay(Player* Enemy)
{
	ifstream m_fLoad;
	int tmpx, tmpy, check;
	int x, y, iCount = 0;
	m_fLoad.open("Replay.txt");
	if (m_fLoad.is_open())
	{
		m_fLoad >> check >> Enemy->m_strStone >> m_strStone >> Enemy->m_iStoneCount;
		m_fLoad >> Enemy->m_strName >> m_strName;
		m_fLoad >> x >> y;
		if (x == 0)
		{
			Enemy->m_bWin = true;
			while (!m_fLoad.eof())
			{
				m_fLoad >> tmpx >> tmpy;
				DrawStone(tmpx, tmpy);
				Sleep(500);
				m_fLoad >> tmpx >> tmpy;
				Enemy->DrawStone(tmpx, tmpy);
				Sleep(500);
				iCount++;
			}
		}
		else
		{
			m_bWin = true;
			while (!m_fLoad.eof())
			{
				m_fLoad >> tmpx >> tmpy;
				DrawStone(tmpx, tmpy);
				Sleep(500);
				if (iCount < Enemy->m_iStoneCount)
				{
					m_fLoad >> tmpx >> tmpy;
					Enemy->DrawStone(tmpx, tmpy);
					Sleep(500);
				}
				iCount++;
			}
		}
		/*m_bSaved = false;
		Enemy->m_bSaved = false;*/
	}
}

Player::~Player()
{
}