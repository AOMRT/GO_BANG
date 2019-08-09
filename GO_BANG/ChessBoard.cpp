#include "framework.h"
#include "ChessBoard.h"


ChessBoard::ChessBoard(const LINE_NUM& rowCount, const LINE_NUM& colCount):m_rowCount(rowCount),m_colCount(colCount)
{
	m_map.resize(rowCount);
	for (UINT16 i = 0; i < rowCount; i++) 
	{
		m_map[i].assign(colCount, EMPTY);
	}
}


ChessBoard::~ChessBoard()
{
}

void ChessBoard::PrintBoard(const HDC& dc, const RECT& rect)
{
	m_unit = min(((rect.bottom - rect.top) / (m_rowCount + 1)), ((rect.right - rect.left) / (m_colCount + 1)));
	int distanceto_top = (rect.bottom - rect.top - m_unit * (m_rowCount - 1)) / 2;
	int distanceto_left = (rect.right - rect.left - m_unit * (m_colCount - 1)) / 2;
	m_topleft = { rect.left + distanceto_left,rect.top + distanceto_top };

	//绘制棋盘
	for (UINT i = 0; i < m_colCount; i++) {
		POINT point;
		MoveToEx(dc, rect.left + i * m_unit + distanceto_left, rect.top + distanceto_top, &point);
		LineTo(dc, rect.left + i * m_unit + distanceto_left, rect.top + distanceto_top + m_unit * (m_rowCount - 1));
	}
	for (UINT i = 0; i < m_rowCount; i++) {
		POINT point;
		MoveToEx(dc, rect.left + distanceto_left, rect.top + i * m_unit + distanceto_top, &point);
		LineTo(dc, rect.left + distanceto_left + m_unit * (m_colCount - 1), rect.top + i * m_unit + distanceto_top);
	}
	//绘制棋子
	for (UINT i = 0; i < m_chesseslog.size(); i++)
	{
		m_chesseslog[i].Print(dc,m_topleft,m_unit);
	}
}

bool ChessBoard::position_isEmpty(Chess_Point& chess)
{
	if (m_map[chess.getPos().m_row][chess.getPos().m_col] == EMPTY)
		return true;
	else
		return false;
}

bool ChessBoard::position_isLegal(Chess_Point& chess)
{
	if (chess.getPos().m_col > -1 &&
		chess.getPos().m_row > -1 &&
		chess.getPos().m_col < m_colCount &&
		chess.getPos().m_row < m_rowCount
		)
		return true;
	else
		return false;
}


bool ChessBoard::putChesses(Chess_Point& chess)
{
	if (!position_isLegal(chess))
		return false;
	if (!position_isEmpty(chess))
		return false;

	m_chesseslog.push_back(chess);
	if (chess.getType() == BLACK_CHESS)
		m_map[chess.getPos().m_row][chess.getPos().m_col] = BLACK;
	else
		m_map[chess.getPos().m_row][chess.getPos().m_col] = WHITE;
	if (m_chesseslog.size() > 1)
	{
		m_chesseslog[m_chesseslog.size() - 1].setLast();
		m_chesseslog[m_chesseslog.size() - 2].setnotLast();
	}
	return true;
}

bool ChessBoard::chickwinner()
{
	UINT16 lineCount[] = { 1, 1, 1, 1 };			//四个方向连子计数
	bool flag[8] = { false };
	bool baseType = m_chesseslog.back().getType();
	UINT row = m_chesseslog.back().getPos().m_row;
	UINT col = m_chesseslog.back().getPos().m_col;
	for (INT16 j = 0; j < 4; ++j) 
	{
		for (INT16 i = 1; i < 5; ++i)
		{
			switch (j)
			{
			case 0:
				if (flag[0] == false && (row + i) < m_rowCount && chickMark(m_map[row + i][col], baseType))
					++lineCount[j];
				else
					flag[0] = true;
				if (flag[1] == false && (((int)row - i) >= 0) && chickMark(m_map[row - i][col], baseType))
					++lineCount[j];
				else
					flag[1] = true;
				break;
			case 1:
				if (flag[2] == false && (col + i) < m_colCount && chickMark(m_map[row][col + i], baseType))
					++lineCount[j];
				else
					flag[2] = true;
				if (flag[3] == false && (((int)col - i) >= 0) && chickMark(m_map[row][col - i], baseType))
					++lineCount[j];
				else
					flag[3] = true;
				break;
			case 2:
				if (flag[4] == false && (col + i) < m_colCount && (row + i) < m_rowCount && chickMark(m_map[row + i][col + i], baseType))
					++lineCount[j];
				else
					flag[4] = true;
				if (flag[5] == false && (((int)col - i) >= 0) && ((int)(row - i) >= 0) && chickMark(m_map[row - i][col - i], baseType))
					++lineCount[j];
				else
					flag[5] = true;
				break;
			case 3:
				if (flag[6] == false && (col + i) < m_colCount && (((int)row - i) >= 0) && chickMark(m_map[row - i][col + i], baseType))
					++lineCount[j];
				else
					flag[6] = true;
				if (flag[7] == false && (((int)col - i) >= 0) && (row + i) < m_rowCount && chickMark(m_map[row + i][col - i], baseType))
					++lineCount[j];
				else
					flag[7] = true;
				break;
			default:
				break;
			}
			if (lineCount[j] >= 5)
				return true;
		}
	}
	return false;
}

bool ChessBoard::chickMark(ChessMark& mark, bool type)
{
	if((mark==WHITE&&type== WHITE_CHESS)||(mark == BLACK && type == BLACK_CHESS))
		return true;
	else
		return false;
}



Chess_pos ChessBoard::dateTopos(const LONG& x, const LONG& y)
{
	if (m_unit <= 0)
	{
		return { 0,0 };
	}
	int row = int((x - m_topleft.x + m_unit / 2) / m_unit);
	int col = int((y - m_topleft.y + m_unit / 2) / m_unit);
	return Chess_pos(row, col);
}
