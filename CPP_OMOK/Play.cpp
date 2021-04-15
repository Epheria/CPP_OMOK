#include "Play.h"

Play::Play()
{
	m_ix = 0;
	m_iy = 0;
	m_iWidth = 20;
	m_iHeight = 30;
	m_iTurn = 1;
	P1 = new Player((m_ix + m_iWidth) * 0.5f, m_iy + (m_iHeight * 0.5f));
	P1->SetShape("☞");
	P1->SetStone("○");
	P2 = new Player((m_ix + m_iWidth) * 0.5f, m_iy + (m_iHeight * 0.5f));
	P2->SetShape("☜");
	P2->SetStone("●");
}

void Play::ReConstruct()
{
	m_ix = 0;
	m_iy = 0;
	m_iWidth = 20;
	m_iHeight = 30;
	m_iTurn = 1;
	P1 = new Player((m_ix + m_iWidth) * 0.5f, m_iy + (m_iHeight * 0.5f));
	P1->SetShape("☞");
	P1->SetStone("○");
	P2 = new Player((m_ix + m_iWidth) * 0.5f, m_iy + (m_iHeight * 0.5f));
	P2->SetShape("☜");
	P2->SetStone("●");
}

void Play::ShowMenu()
{
	string tmp, tmp1;
	while (1)
	{
		system("cls");
		m_DrawManager.BoxDraw(m_ix, m_iy, m_iWidth, m_iHeight);
		m_DrawManager.DrawMidText("★ 오 목 ★", m_iWidth, m_iHeight / 4);
		m_DrawManager.DrawMidText("1.게임 시작", m_iWidth, m_iHeight / 4 + 2);
		m_DrawManager.DrawMidText("2.옵션 설정", m_iWidth, m_iHeight / 4 + 4);
		m_DrawManager.DrawMidText("3.게임 종료", m_iWidth, m_iHeight / 4 + 6);
		if (P1->GetCheckSavedReplay() == true)
		{
			m_DrawManager.DrawMidText("4.게임 리플레이", m_iWidth, m_iHeight / 4 + 8);
		}
		m_DrawManager.BoxDraw(m_iWidth / 2, m_iHeight / 4 + 10, m_iWidth / 2, 3);
		m_iMenuSelect = m_DrawManager.Input(m_iWidth, m_iHeight / 4 + 11);

		switch (m_iMenuSelect)
		{
		case 1:
			system("cls");
			if (P1->GetCheckSaved() == false && P2->GetCheckSaved() == false)
			{
				ReConstruct();
				m_DrawManager.BoxDraw(m_ix, m_iy, m_iWidth, m_iHeight);
				m_DrawManager.DrawMidText("P1 이름", m_iWidth, m_iHeight / 4);
				m_DrawManager.DrawMidText("입력 : ", m_iWidth, m_iHeight / 4 + 2);
				tmp = m_DrawManager.InputName(m_iWidth + 4, m_iHeight / 4 + 2);
				P1->SetName(tmp);

				m_DrawManager.DrawMidText("P2 이름", m_iWidth, m_iHeight / 4 + 8);
				m_DrawManager.DrawMidText("입력 : ", m_iWidth, m_iHeight / 4 + 10);
				tmp = m_DrawManager.InputName(m_iWidth + 4, m_iHeight / 4 + 10);
				P2->SetName(tmp);
			}
			else
			{
				P1->LoadInfo(P2);
				m_iTurn = P1->GetTurn();
				if (P2->GetStoneCount() < P1->GetStoneCount())
				{
					Player* tmp = P1;
					P1 = P2;
					P2 = tmp;
				}
			}
			GameDraw();
			break;
		case 2:
			m_DrawManager.BoxDraw(m_ix, m_iy, m_iWidth, m_iHeight);
			ShowOption();
			break;
		case 3:
			P1->ClearStone();
			P2->ClearStone();
			return;
		case 4:
			system("cls");

			m_DrawManager.BoxDraw(m_ix, m_iy, m_iWidth, m_iHeight);
			P1->LoadReplay(P2);
			if (P1->GetWin() == true)
				tmp1 = P1->GetName();
			else if (P2->GetWin() == true)
				tmp1 = P2->GetName();

			m_DrawManager.DrawMidText(tmp1, m_iWidth - 2, m_iHeight / 4);
			m_DrawManager.DrawMidText("팀 승리!!", m_iWidth + 4, m_iHeight / 4);
			system("pause");
			//P1->InitFile();
			break;
		default:
			continue;
		}
	}
}

void Play::GameDraw()
{
	P1->SetWidthHeight(m_iWidth, m_iHeight);
	P2->SetWidthHeight(m_iWidth, m_iHeight);
	int iInputCheck;
	int iUndoCount = P1->GetUndoCount();
	string tmp1, tmp2;
	Player* CurPlayer = P1, * EnemyPlayer = P2;

	system("cls");
	m_DrawManager.BoxDraw(m_ix, m_iy, m_iWidth, m_iHeight);

	while (1)
	{
		while (1)
		{
			EnemyPlayer->ReDrawStone();
			CurPlayer->ReDrawStone();
			CurPlayer->Draw();
			m_bPlayCheck = true;
			ShowGmaeStatus(CurPlayer);
			iInputCheck = CurPlayer->Move(m_ix, m_iy, m_iWidth, m_iHeight, m_iTurn, EnemyPlayer);
			switch (iInputCheck)
			{
			case INPUT_TYPE_MOVE:

				break;
			case INPUT_TYPE_DROP:
			{
				CurPlayer->CreateStone();
				CurPlayer->DrawStone();
				if (CurPlayer->ReturnWinner() == true)
				{
					CurPlayer->SaveReplay(EnemyPlayer);

					tmp1 = CurPlayer->GetName();
					m_DrawManager.DrawMidText(tmp1, m_iWidth - 2, m_iHeight / 4);
					m_DrawManager.DrawMidText("팀 승리!!", m_iWidth + 4, m_iHeight / 4);
					system("pause");
					CurPlayer->ClearStone();
					EnemyPlayer->ClearStone();
					m_iTurn = 1;
					m_bPlayCheck = false;
					P1->InitFile();
					return;
				}
				m_iTurn++;
				Player* tmp = CurPlayer;
				CurPlayer = EnemyPlayer;
				EnemyPlayer = tmp;
			}
			break;

			case INPUT_TYPE_OPTION:
				ShowOption();
				m_DrawManager.BoxDraw(m_ix, m_iy, m_iWidth, m_iHeight);
				CurPlayer->ReDrawStone();
				EnemyPlayer->ReDrawStone();
				CurPlayer->ClearStone();
				EnemyPlayer->ClearStone();
				break;

			case INPUT_TYPE_EXIT:
			{
				CurPlayer->SetTurn(m_iTurn);
				CurPlayer->SaveInfo(EnemyPlayer);
				P1->ClearStone();
				P2->ClearStone();
				//m_iTurn = 1;
				/*CurPlayer->InitPos();
				EnemyPlayer->InitPos();
				CurPlayer->SetUndoCount(4);
				EnemyPlayer->SetUndoCount(4);*/
				return;
			}
			case INPUT_TYPE_UNDO:
				if (m_iTurn > 1 && CurPlayer->GetUndoCount() > 0)
				{
					iUndoCount = CurPlayer->GetUndoCount();
					iUndoCount--;
					CurPlayer->SetUndoCount(iUndoCount);
					m_iTurn--;
					EnemyPlayer->EraseStone();
					EnemyPlayer->ReDrawMap(m_iWidth, m_iHeight);
					Player* tmp = CurPlayer;
					CurPlayer = EnemyPlayer;
					EnemyPlayer = tmp;
				}
				else
					continue;

			}
			if (iInputCheck == INPUT_TYPE_DROP || iInputCheck == INPUT_TYPE_UNDO)
				break;
		}
	}
}

void Play::ShowGmaeStatus(Player* P)
{
	string tmp;
	tmp = P->GetName();
	m_DrawManager.DrawMidText("====조작키====", m_iWidth, m_iHeight + 1);
	m_DrawManager.DrawMidText("이동 : A,S,W,D  돌놓기 : ENTER", m_iWidth, m_iHeight + 2);
	m_DrawManager.DrawMidText("무르기 :N  옵션 : P  종료 : ESC", m_iWidth, m_iHeight + 3);
	m_DrawManager.DrawMidText("Player Name : ", m_iWidth, m_iHeight + 4);
	m_DrawManager.DrawMidText(tmp, m_iWidth + 6, m_iHeight + 4);
	m_DrawManager.DrawMidText("무르기 : ", m_iWidth + 16, m_iHeight + 4);
	if (P->GetUndoCount() >= 10)
		m_DrawManager.IntDraw(P->GetUndoCount(), m_iWidth + 19, m_iHeight + 4);
	else
		m_DrawManager.IntDraw(P->GetUndoCount(), m_iWidth + 20, m_iHeight + 4);

	m_DrawManager.DrawMidText("Turn : ", m_iWidth, m_iHeight + 5);
	m_DrawManager.IntDraw(m_iTurn, m_iWidth + 4, m_iHeight + 5);

}

void Play::ShowOption()
{
	int tWidth, tHeight;
	int iCursor;
	while (1)
	{
		system("cls");
		m_DrawManager.BoxDraw(m_ix, m_iy, m_iWidth, m_iHeight);
		m_DrawManager.DrawMidText("= Option =", m_iWidth, m_iHeight / 4);
		m_DrawManager.DrawMidText("1.Map Size Set", m_iWidth, m_iHeight / 4 + 2);
		m_DrawManager.DrawMidText("2.Cursor Custom", m_iWidth, m_iHeight / 4 + 4);
		m_DrawManager.DrawMidText("3.Stone Custom", m_iWidth, m_iHeight / 4 + 6);
		m_DrawManager.DrawMidText("4.Undo Count Set", m_iWidth, m_iHeight / 4 + 8);
		m_DrawManager.DrawMidText("5.Return", m_iWidth, m_iHeight / 4 + 10);
		m_DrawManager.DrawMidText("입력 : ", m_iWidth, m_iHeight / 4 + 12);
		m_iOptSelect = m_DrawManager.Input(m_iWidth + 4, m_iHeight / 4 + 12);

		if ((m_iOptSelect == 1 && m_bPlayCheck == true) || (m_iOptSelect == 4 && m_bPlayCheck == true))
		{
			system("cls");
			m_DrawManager.DrawMidText("접근 불가능", m_iWidth, m_iHeight / 4);
			m_DrawManager.DrawMidText("(Game Play중)", m_iWidth, m_iHeight / 4 + 2);
			system("pause");
			continue;
		}

		switch (m_iOptSelect)
		{
		case 1:
			system("cls");
			m_DrawManager.BoxDraw(m_ix, m_iy, m_iWidth, m_iHeight);
			m_DrawManager.DrawMidText("Width : ", m_iWidth, m_iHeight / 4);
			tWidth = m_DrawManager.Input(m_iWidth + 4, m_iHeight / 4);
			m_DrawManager.DrawMidText("Height : ", m_iWidth, m_iHeight / 4 + 4);
			tHeight = m_DrawManager.Input(m_iWidth + 4, m_iHeight / 4 + 4);

			if ((tWidth < 20 || tWidth > 90) && (tHeight < 20 || tHeight > 45))
			{
				system("cls");
				m_DrawManager.BoxDraw(m_ix, m_iy, m_iWidth, m_iHeight);
				m_DrawManager.DrawMidText("변경 불가능", m_iWidth, m_iHeight / 4);
				m_DrawManager.DrawMidText("<가로 : 20 ~ 90 , 세로 : 20 ~ 45>", m_iWidth, m_iHeight / 4 + 4);
				system("pause");
				break;
			}
			else
			{
				m_iWidth = tWidth;
				m_iHeight = tHeight;
				break;
			}
		case 2:
			system("cls");
			m_DrawManager.BoxDraw(m_ix, m_iy, m_iWidth, m_iHeight);
			m_DrawManager.DrawMidText("= Set Cursor =", m_iWidth, m_iHeight / 4);
			m_DrawManager.DrawMidText("1.○,●", m_iWidth, m_iHeight / 4 + 2);
			m_DrawManager.DrawMidText("2.♡,♥", m_iWidth, m_iHeight / 4 + 4);
			m_DrawManager.DrawMidText("3.☞,☜", m_iWidth, m_iHeight / 4 + 6);
			m_DrawManager.DrawMidText("4.①,②", m_iWidth, m_iHeight / 4 + 8);
			m_DrawManager.DrawMidText("5.Return", m_iWidth, m_iHeight / 4 + 10);
			m_DrawManager.DrawMidText("입력 : ", m_iWidth, m_iHeight / 4 + 12);
			iCursor = m_DrawManager.Input(m_iWidth + 4, m_iHeight / 4 + 12);
			switch (iCursor)
			{
			case 1:
				P1->SetShape("○");
				P2->SetShape("●");
				break;
			case 2:
				P1->SetShape("♡");
				P2->SetShape("♥");
				break;
			case 3:
				P1->SetShape("☞");
				P2->SetShape("☜");
				break;
			case 4:
				P1->SetShape("①");
				P2->SetShape("②");
				break;
			case 5:
				break;
			}
			break;

		case 3:
			system("cls");
			m_DrawManager.BoxDraw(m_ix, m_iy, m_iWidth, m_iHeight);
			m_DrawManager.DrawMidText("= Set Stone =", m_iWidth, m_iHeight / 4);
			m_DrawManager.DrawMidText("1.○,●", m_iWidth, m_iHeight / 4 + 2);
			m_DrawManager.DrawMidText("2.♡,♥", m_iWidth, m_iHeight / 4 + 4);
			m_DrawManager.DrawMidText("3.☏,☎", m_iWidth, m_iHeight / 4 + 6);
			m_DrawManager.DrawMidText("4.①,②", m_iWidth, m_iHeight / 4 + 8);
			m_DrawManager.DrawMidText("5.Return", m_iWidth, m_iHeight / 4 + 10);
			m_DrawManager.DrawMidText("입력 : ", m_iWidth, m_iHeight / 4 + 12);
			iCursor = m_DrawManager.Input(m_iWidth + 4, m_iHeight / 4 + 12);
			switch (iCursor)
			{
			case 1:
				P1->SetStone("○");
				P2->SetStone("●");
				break;
			case 2:
				P1->SetStone("♡");
				P2->SetStone("♥");
				break;
			case 3:
				P1->SetStone("☏");
				P2->SetStone("☎");
				break;
			case 4:
				P1->SetStone("①");
				P2->SetStone("②");
				break;
			case 5:
				break;
			}
			break;

		case 4:
			UndoMenu();
			break;
		case 5:
			system("cls");
			return;
		default:
			continue;
		}
	}

}

void Play::UndoMenu()
{
	int iSelect;
	int iSetUndo;
	while (1)
	{
		system("cls");
		m_DrawManager.BoxDraw(m_ix, m_iy, m_iWidth, m_iHeight);
		m_DrawManager.DrawMidText("= Set Undo =", m_iWidth, m_iHeight / 4 + 2);
		m_DrawManager.DrawMidText("1.Set Undo Count", m_iWidth, m_iHeight / 4 + 4);
		m_DrawManager.DrawMidText("2. Undo off", m_iWidth, m_iHeight / 4 + 6);
		m_DrawManager.DrawMidText("3. Return", m_iWidth, m_iHeight / 4 + 8);
		m_DrawManager.DrawMidText("입력 : ", m_iWidth, m_iHeight / 4 + 10);
		iSelect = m_DrawManager.Input(m_iWidth + 4, m_iHeight / 4 + 10);

		switch (iSelect)
		{
		case 1:
			while (1)
			{
				system("cls");
				m_DrawManager.BoxDraw(m_ix, m_iy, m_iWidth, m_iHeight);
				m_DrawManager.DrawMidText("무르기 횟수 입력(최대 10회) : ", m_iWidth, m_iHeight / 4 + 2);
				iSetUndo = m_DrawManager.Input(m_iWidth + 16, m_iHeight / 4 + 2);
				if (iSetUndo > 10 || iSetUndo < 0)
				{
					m_DrawManager.DrawMidText("범위가 맞지 않습니다 ( 0 ~ 10 ) ", m_iWidth, m_iHeight / 4 + 4);
					system("pause");
					continue;
				}
				else
				{
					P1->SetUndoCount(iSetUndo);
					P2->SetUndoCount(iSetUndo);
					return;
				}
			}
		case 2:
			P1->SetUndoCount(0);
			P2->SetUndoCount(0);
		case 3:
			return;
		}
	}
}

Play::~Play()
{

}