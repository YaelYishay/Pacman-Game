#pragma once
#include "Object.h"

enum Direction{
	UP, DOWN, RIGHT, LEFT, STOP
};

class DynamicObject : public Object
{
public:
	DynamicObject(IntRect p, Color c, Texture t) : Object(p, c, t) { ; }
	DynamicObject() { ; }
	~DynamicObject();

	virtual void draw(RenderWindow &)const = 0;
	virtual void move(float) = 0;
	void setDirection(Direction d) { m_direction = d; }


protected:
	Direction m_direction;
	IntRect m_lastPosition;
	IntRect m_initialPosition;
};

