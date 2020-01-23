#include "stdafx.h"
#include "Random.h"
#include <iostream>

Random::~Random()
{
}

//controll random movement of random demon
void Random::move(float deltaTime)
{
	m_lastPosition = m_position;
	static float lastMove = 0;

	if (deltaTime - lastMove < 1 / 600.f)
		return;

	lastMove = deltaTime;

	switch (m_direction)
	{
	case UP:
		m_position.top -= 1;
		break;
	case DOWN:
		m_position.top += 1;
		break;
	case RIGHT:
		m_position.left += 1;
		break;
	case LEFT:
		m_position.left -= 1;
		break;
	default:
		setDirection((Direction)(rand() % 4));
		break;
	}

}

//controll collision of random demon with any object
bool Random::collideWith(Object & otherObject) {
	return otherObject.collideWith(*this);
}

//for double-dispach
bool Random::collideWith(Demon &) {
	return false;
}

//controll collision with pac
bool Random::collideWith(Player &) {
	m_position = m_initialPosition;
	return false;
}

//controll collision with wall
bool Random::collideWith(Wall &) {
	m_position = m_lastPosition;
	setDirection((Direction)(rand() % 4));
	return false;
}

//for double-dispach
bool Random::collideWith(Cookie &) {
	return false;
}
