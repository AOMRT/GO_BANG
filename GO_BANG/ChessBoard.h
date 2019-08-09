#pragma once

#ifndef _CHESS_POINT_
#define _CHESS_POINT_
#include "Chess_Point.h"
#endif // !_CHESS_POINT_


enum ChessMark
{
	EMPTY = -1,
	WHITE = 0,
	BLACK = 1
};

typedef std::vector<std::vector<ChessMark>>		Chess_Map;
typedef std::vector<Chess_Point>				Chess_log;




class ChessBoard
{
private:
	LINE_NUM m_rowCount;
	LINE_NUM m_colCount;
	UINT_SIZE m_unit;
	POINT m_topleft;
	Chess_log m_chesseslog;
	Chess_Map m_map;

public:
	ChessBoard(const LINE_NUM& rowCount, const LINE_NUM& colCount);
	~ChessBoard();

	void PrintBoard(const HDC& dc, const RECT& rect);
	bool position_isEmpty(Chess_Point& chess);
	bool position_isLegal(Chess_Point& chess);
	bool putChesses(Chess_Point& chess);
	bool chickwinner();
	bool chickMark(ChessMark& mark, bool type);
	Chess_pos dateTopos(const LONG& x, const LONG& y);
};

