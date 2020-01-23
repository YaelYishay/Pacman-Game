#pragma once
#include "Demon.h"

class Random :public Demon
{
public:
	Random(IntRect p, Color c, Texture t) : Demon(p, c, t) { m_initialPosition = p; m_direction = UP; }
	~Random();
	virtual void move(float);
	virtual bool collideWith(Object&);
	virtual bool collideWith(Demon&);
	virtual bool collideWith(Player&);
	virtual bool collideWith(Wall&);
	virtual bool collideWith(Cookie&);

};

