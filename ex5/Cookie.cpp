#include "stdafx.h"
#include "Cookie.h"
#include <iostream>
#include "controller.h"

//c-tor
Cookie::Cookie(IntRect p, Color c, Texture t, CookieType type)
	:StaticObject(p, c, t),
	m_type(type)
{
}

Cookie::~Cookie()
{
}

//draw the cookie object onto the board
void Cookie::draw(RenderWindow & window)const
{
	sf::Sprite sp;
	sp.setTexture(m_pic);
	sp.setColor(m_color);
	sp.setPosition((float)m_position.left, (float)m_position.top);
	window.draw(sp);
}

//double-dispach collide control with object
bool Cookie::collideWith(Object &otherObject){
	return otherObject.collideWith(*this);
}

//double-dispach collide control with demon
bool Cookie::collideWith(Demon &otherObject){
	return false;
}

//double-dispach collide control with player
bool Cookie::collideWith(Player &otherObject){
	return true;
}
//double-dispach collide control with wall
bool Cookie::collideWith(Wall &otherObject){
	return false;
}

//double-dispach collide control with cookie
bool Cookie::collideWith(Cookie &otherObject){
	return false;
}

//controlls the cookies speed affect on pac
void Cookie::cookieEffect(float& speed) const
{
	//calculate time
	static float lastTime = 0;
	float time = controller::instance().loadClock().getElapsedTime().asSeconds();

	//check if has affect
	if (lastTime != 0) {
		if ((m_type == HEALTH && abs(time - lastTime) < 14.f) ||
			(m_type == POISON && abs(time - lastTime) < 7.f))
			return;
	}

	lastTime = time;

	//set speed by cookie type
	switch (m_type)
	{
	case HEALTH:
		controller::instance().restartClock();
		speed -= (float)(speed*0.20);
		break;
	case POISON:
		controller::instance().restartClock();
		speed += (float)(speed*0.10);
		break;
	default:
		break;
	}


}