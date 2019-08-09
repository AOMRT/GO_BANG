#pragma once

#ifndef _CHESS_POINT_
#define _CHESS_POINT_
#include "Chess_Point.h"
#endif // !_CHESS_POINT_


#ifndef _CHESS_BOARD_
#define _CHESS_BOARD_
#include "ChessBoard.h"
#endif // !_CHESS_BOARD_

#ifndef _GAME_PLAYER_
#define _GAME_PLAYER_
#include "GamePlayer.h"
#endif // !_GAME_PLAYER_




enum GameMode
{
	PLAYER_VS_PLAYER,
	PLAYER_VS_AI,
	AI_VS_AI
};
enum GameStation
{
	GAME_START,
	WAIT_INPUT,
	TURN_TO_PLAYER1,
	TURN_TO_PLAYER2,
	PLAYER1_IS_WINNER,
	PLAYER2_IS_WINNER,
	GAME_END
};

class Game_Application
{
private:
	ChessBoard m_board;
	GamePlayer m_player[2];
	GameMode m_mode;
	GameStation m_station;
public:
	Game_Application(const LINE_NUM& rowCount, const LINE_NUM& colCount, const GameMode& mode);
	~Game_Application();


	
	void Print(const HDC& dc, const RECT& rect);
	void TheLeftMouseChick(const HWND& hWnd, const LONG& x, const LONG& y);
};

