#include "stdafx.h"
#include "Object.h"
#include <iostream>

//abstract class

Object::Object(IntRect position, Color color, Texture txture)
	: m_position(position), m_color(color), m_pic(txture)
{
}

Object::~Object()
{
}
