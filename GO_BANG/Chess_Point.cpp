#include "framework.h"
#include "Chess_Point.h"


Chess_Point::Chess_Point()
{
}

Chess_Point::Chess_Point(Chess_pos& _pos, bool _type):m_pos(_pos),m_type(_type)
{
}

Chess_Point::Chess_Point(int _col, int _row, bool _type):m_pos(_col,_row),m_type(_type)
{
}


Chess_Point::~Chess_Point()
{
}

Chess_pos Chess_Point::getPos() const
{
	return m_pos;
}

void Chess_Point::setPos(const Chess_pos& _pos)
{
	m_pos = _pos;
}

void Chess_Point::setType(const bool _type)
{
	m_type = _type;
}

bool Chess_Point::getType() const
{
	return m_type;
}

bool Chess_Point::isLast() const
{
	return is_lastChess;
}

void Chess_Point::setLast()
{
	is_lastChess = IS_LAST;
}

void Chess_Point::setnotLast()
{
	is_lastChess = NOT_LAST;
}

void Chess_Point::Print(const HDC& dc, const POINT& topleft, const UINT_SIZE unit)
{
	POINT pos = { topleft.x + unit * m_pos.m_col,topleft.y + unit * m_pos.m_row };
	if (is_lastChess)
	{
		UINT_SIZE side = unit / 2 - 1;

		HPEN pen = CreatePen(PS_SOLID, unit/15, 0x7fff00);
		HGDIOBJ obj = SelectObject(dc, pen);
		Rectangle(dc, pos.x - side, pos.y - side, pos.x + side, pos.y + side);
		SelectObject(dc, obj);
	}

	HBRUSH brush = CreateSolidBrush(m_type ? 0 : 0xffffff);
	HBRUSH brs = (HBRUSH)SelectObject(dc, brush);
	INT radio = unit / 2 - max((unit + 10) / 20, 1);
	Ellipse(dc, pos.x - radio, pos.y - radio, pos.x + radio, pos.y + radio);
	SelectObject(dc, brs);
}

bool Chess_pos::operator==(const Chess_pos& pos)
{
	if (this->m_col == pos.m_col && this->m_row == pos.m_row)
		return true;
	else
		return false;
}
