#pragma once
#include "Object.h"

class StaticObject :public Object
{
public:
	StaticObject(IntRect p, Color c, Texture t) :Object(p, c, t) { ; }
	~StaticObject();

	virtual void draw(RenderWindow &)const = 0;

};

