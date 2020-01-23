#include "stdafx.h"
#include "Wall.h"
#include <iostream>

Wall::~Wall()
{
}

//display wall on board
void Wall::draw(RenderWindow &window)const
{
	sf::Sprite sp;
	sp.setTexture(m_pic);
	sp.setColor(m_color);
	sp.setPosition((float)m_position.left, (float)m_position.top);
	window.draw(sp);
}

//controll collision with any object
bool Wall::collideWith(Object &otherObject){
	return otherObject.collideWith(*this);
}

//controll collision with demon
bool Wall::collideWith(Demon &otherObject){
	return false;
}

//controll collision with player
bool Wall::collideWith(Player &otherObject){

	return false;
}

//for double-dispach
bool Wall::collideWith(Wall &otherObject){
	return false;
}
//for double dispach
bool Wall::collideWith(Cookie &otherObject){
	return false;
}