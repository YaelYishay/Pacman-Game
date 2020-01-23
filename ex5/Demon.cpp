#include "stdafx.h"
#include "Demon.h"
//abstract class

Demon::~Demon()
{
}

//draw demons to window
void Demon::draw(RenderWindow &window) const
{
	
	sf::Sprite sp;
	sp.setTexture(m_pic);
	sp.setColor(m_color);
	sp.setPosition((float)m_position.left, (float)m_position.top);
	window.draw(sp);
}

