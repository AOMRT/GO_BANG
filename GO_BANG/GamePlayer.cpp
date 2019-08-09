#include "GamePlayer.h"


GamePlayer::GamePlayer()
{
}

GamePlayer::GamePlayer(const PLAYER_TYPE& _type, const PLAYER_SIDE& _side):m_side(_side),m_type(_type)
{
}

GamePlayer::~GamePlayer()
{
}

void GamePlayer::setSide(const PLAYER_SIDE& _side)
{
	m_side = _side;
}

void GamePlayer::setType(const PLAYER_TYPE& _type)
{
	m_type = _type;
}

PLAYER_TYPE GamePlayer::getType()
{
	return m_type;
}

PLAYER_SIDE GamePlayer::getSide()
{
	return m_side;
}

PLAYER_TYPE GamePlayer::is_ai()
{
	if (m_side == IS_AI)
		return true;
	else
		return false;
}
