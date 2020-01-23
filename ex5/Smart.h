#pragma once
#include "Demon.h"
#include "Player.h"


class Smart :public Demon
{
public:
	Smart(IntRect, Color, Texture, Player&);
	~Smart();
	void move(float);

	virtual bool collideWith(Object&);
	virtual bool collideWith(Demon&);
	virtual bool collideWith(Player&);
	virtual bool collideWith(Wall&);
	virtual bool collideWith(Cookie&);

protected:
	int distance(IntRect, IntRect) const;
	void smartRoute(IntRect);
	Player &m_pac;

};

