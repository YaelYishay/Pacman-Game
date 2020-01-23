#pragma once
#include "StaticObject.h"

class Wall :public StaticObject
{
public:
	Wall(IntRect p, Color c, Texture t) :StaticObject(p, c, t) { ; }
	~Wall();
	void draw(RenderWindow &)const override;
	virtual bool collideWith(Object&);
	virtual bool collideWith(Demon&);
	virtual bool collideWith(Player&);
	virtual bool collideWith(Wall&);
	virtual bool collideWith(Cookie&);

};

