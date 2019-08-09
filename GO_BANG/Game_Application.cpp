#include "framework.h"
#include "Game_Application.h"



Game_Application::Game_Application(const LINE_NUM& rowCount, const LINE_NUM& colCount, const GameMode& mode) :m_board(rowCount, colCount)
{
	m_station = TURN_TO_PLAYER1;
	switch (mode)
	{
	case PLAYER_VS_PLAYER:
		m_player[0].setType(IS_PLAYER);
		m_player[1].setType(IS_PLAYER);
		break;
	case PLAYER_VS_AI:
		m_player[0].setType(IS_PLAYER);
		m_player[1].setType(IS_AI);
		break;
	case AI_VS_AI:
		m_player[0].setType(IS_AI);
		m_player[1].setType(IS_AI);
		break;
	default:
		break;
	}
	m_player[0].setSide(WHITE_SIDE);
	m_player[1].setSide(BLACK_SIDE);
}

Game_Application::~Game_Application()
{
}

void Game_Application::Print(const HDC& dc, const RECT& rect)
{
	m_board.PrintBoard(dc, rect);
}
/* 触发按键事件 */
void Game_Application::TheLeftMouseChick(const HWND& hWnd, const LONG& x, const LONG& y)
{
	//像素坐标换算棋盘坐标
	Chess_pos p = m_board.dateTopos(x, y);

	//判断下棋方并记录
	if (m_station == TURN_TO_PLAYER1)
	{
		Chess_Point point(p, m_player[0].getSide());
		if (m_board.putChesses(point))
		{
			m_station = TURN_TO_PLAYER2;
			InvalidateRect(hWnd, NULL, true);
		}
	}
	else if (m_station == TURN_TO_PLAYER2)
	{
		Chess_Point point(p, m_player[1].getSide());
		if (m_board.putChesses(point))
		{
			m_station = TURN_TO_PLAYER1;
			InvalidateRect(hWnd, NULL, true);
		}
	}
	//胜利判定
	if (m_board.chickwinner())
	{
		if (m_station == TURN_TO_PLAYER1)
			m_station = PLAYER2_IS_WINNER;
		else if(m_station == TURN_TO_PLAYER2)
			m_station = PLAYER1_IS_WINNER;
	}
	if (m_station == PLAYER1_IS_WINNER ||m_station == PLAYER2_IS_WINNER)
	{
		if (m_station == PLAYER1_IS_WINNER)
			MessageBoxA(hWnd, "PLAYER1_IS_WINNER", "tip", MB_OK);
		else
			MessageBoxA(hWnd, "PLAYER2_IS_WINNER", "tip", MB_OK);
		return;
	}
}
