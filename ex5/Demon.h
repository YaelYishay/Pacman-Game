#pragma once
#include "DynamicObject.h"


class Demon : public DynamicObject
{
public:
	Demon(IntRect p, Color c, Texture t) :DynamicObject(p, c, t) { ; }
	Demon() { ; }
	~Demon();
	void draw(RenderWindow &)const override;
	virtual void move(float) = 0;


};

