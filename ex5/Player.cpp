#include "stdafx.h"
#include "Player.h"
#include <iostream>

const int RADIUS = 100;

//c-tor
Player::Player()
	: m_dataFont(DataBase::instance().loadFont(FONT)),
	m_lives(3),
	m_score(0),
	m_level(1),
	m_speed(1 / 400.f)
{
	m_initialPosition = m_position;

	for (size_t i = 0; i < 3; i++) {
		m_data.push_back(make_unique<Text>());
		m_data[i]->setFont(m_dataFont);
		m_data[i]->setCharacterSize(40);
		m_data[i]->setFillColor(Color::White);
		m_data[i]->setPosition((float)(130 + i * 220), 10);
	}
}

Player::~Player()
{
}

//display pac to board
void Player::draw(RenderWindow &window)const
{
	sf::Sprite sp;
	sp.setTexture(m_pic);
	sp.setPosition((float)m_position.left, (float)m_position.top);
	window.draw(sp);

	m_data[0]->setString(to_string(m_score));
	m_data[1]->setString(to_string(m_lives));
	m_data[2]->setString(to_string(m_level));

	for (size_t i = 0; i < m_data.size(); i++)
		window.draw(*m_data[i]);
}

//controll collision with any object
bool Player::collideWith(Object &otherObject) {
	return otherObject.collideWith(*this);
}

//control collision with demon
bool Player::collideWith(Demon &otherObject)
{
	m_lives--;
	m_position = m_initialPosition;
	m_direction = STOP;
	return false;
}

//for double-dispach
bool Player::collideWith(Player &otherObject) {
	return false;
}

//controll collision with wall
bool Player::collideWith(Wall &otherObject) {
	m_position = m_lastPosition;
	return false;
}

//controll collision with cookie
bool Player::collideWith(Cookie &otherObject)
{
	//calculate distance radius from cookie
	if ((otherObject.getPosition().top - m_position.top > RADIUS / 2) ||
		(otherObject.getPosition().left - m_position.left > RADIUS / 2 ))
		return false;

	m_score += (m_numOfDemons + 1) * 2;
	otherObject.cookieEffect(m_speed);
	return true;
}

//set for player the position ,color and texture for new level
void Player::levelData(IntRect p, Color c, Texture t)
{
	m_color = c;
	m_position = p;
	m_initialPosition = m_position;
	m_pic = t;
}

//set player position
void Player::setPosition(IntRect pos) {
	m_position = pos;
}

//get level number
int Player::getLevel() {
	return m_level;
}

//check if pac is alive
bool Player::isAlive() {
	return (m_lives != 0) ? true : false;
}

//update the players level
void Player::increaseLevel() {
	m_level++;
}

//controll the movement of pac
void Player::move(float deltaTime)
{
	static float lastMove = 0;

	if (deltaTime - lastMove < m_speed)
		return;

	lastMove = deltaTime;

	m_lastPosition = m_position;
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
	case STOP:
		m_position.top -= 0;
		m_position.top += 0;
		m_position.left -= 0;
		m_position.left += 0;
		break;
	default:
		break;
	}
}



