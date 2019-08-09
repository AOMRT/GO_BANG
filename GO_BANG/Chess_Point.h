#pragma once

#define NOT_LAST			false
#define IS_LAST				true
#define WHITE_CHESS			false
#define BLACK_CHESS			true

typedef unsigned int				UINT_SIZE;
typedef unsigned int				LINE_NUM;


struct Chess_pos
{
	UINT16 m_col;
	UINT16 m_row;
	Chess_pos() {};
	Chess_pos(int _col, int _row) :m_col(_col), m_row(_row) {};
	bool operator==(const Chess_pos& pos);
};

class Chess_Point
{
private:

	
	bool is_lastChess;			//最后标记
	bool m_type;
	Chess_pos m_pos;

public:
	Chess_Point();
	Chess_Point(Chess_pos& _pos,bool _type);
	Chess_Point(int _col, int _row, bool _type);
	~Chess_Point();

	Chess_pos getPos()const;
	void setPos(const Chess_pos& _pos);

	void setType(const bool _type);
	bool getType()const;
	bool isLast()const;
	void setLast();
	void setnotLast();
	void Print(const HDC& dc, const POINT& topleft, const UINT_SIZE unit);
	
};

