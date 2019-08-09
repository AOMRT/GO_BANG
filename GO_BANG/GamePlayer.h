#pragma once

typedef bool		PLAYER_TYPE;
typedef bool		PLAYER_SIDE;

#define	BLACK_SIDE				true
#define WHITE_SIDE				false
#define IS_PLAYER				true
#define IS_AI					false

class GamePlayer
{
private:
	PLAYER_TYPE m_type;
	PLAYER_SIDE m_side;


public:
	GamePlayer();
	GamePlayer(const PLAYER_TYPE& _type, const PLAYER_SIDE& _side);
	~GamePlayer();
	void setSide(const PLAYER_SIDE& _side);
	void setType(const PLAYER_TYPE& _type);
	PLAYER_TYPE getType();
	PLAYER_SIDE getSide();

	bool is_ai();
};
