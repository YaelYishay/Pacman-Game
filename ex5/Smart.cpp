#include "stdafx.h"
#include "Smart.h"
#include <iostream>

//c-tor
Smart::Smart(IntRect p, Color c, Texture t, Player& pac)
	:Demon(p, c, t),m_pac(pac)
{
	m_initialPosition = p;
}

Smart::~Smart()
{
}

//controll smart movement
void Smart::move(float deltaTime) {

	m_lastPosition = m_position;
	static float lastMove = 0;

	if (deltaTime - lastMove < 1 / 100.f) {
		smartRoute(m_pac.getPosition());
		return;
	}

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
	}
}

//control collision with any object
bool Smart::collideWith(Object &otherObject) {
	return otherObject.collideWith(*this);
}

//for double-dispach
bool Smart::collideWith(Demon &otherObject) {
	return false;
}

//control collision with pac
bool Smart::collideWith(Player &otherObject) {
	m_position = m_initialPosition;
	return false;
}

//controll colision with wall
bool Smart::collideWith(Wall &otherObject) {
	m_position = m_lastPosition;
	return false;
}

//for double-dispach
bool Smart::collideWith(Cookie &otherObject) {
	return false;
}

//calculate smart route to catch pac
void Smart::smartRoute(IntRect pacPosition) {


	int minDistance = 1000;
	IntRect currPosition = m_position;

	for (size_t direction = 0; direction < 4; direction++) {
		switch (direction)
		{
		case UP:
			currPosition.top -= 1;
			break;
		case DOWN:
			currPosition.top += 1;
			break;
		case RIGHT:
			currPosition.left += 1;
			break;
		case LEFT:
			currPosition.left -= 1;
			break;
		}

		if (distance(pacPosition, currPosition) < minDistance) {
			setDirection((Direction)direction);
			minDistance = distance(pacPosition, currPosition);
		}
	}
}

//calculate distance between two locations
int Smart::distance(IntRect pacLocation, IntRect other) const
{
	return(abs(pacLocation.top - other.top) + abs(pacLocation.left - other.left));

}