#pragma once
#include <SFML/Graphics.hpp>

class Object;
class Cookie;
class Wall;
class Player;
class Demon;
class Smart;

using sf::IntRect;
using sf::Color;
using sf::Texture;
using sf::RenderWindow;

class Object
{
public:
	Object(IntRect, Color, Texture);
	Object() { ; }
	~Object();

	virtual bool collideWith(Object&) = 0;
	virtual bool collideWith(Demon&) = 0;
	virtual bool collideWith(Player&) = 0;
	virtual bool collideWith(Wall&) = 0;
	virtual bool collideWith(Cookie&) = 0;

	virtual void setNumOfDemons(int d) { m_numOfDemons = d; }
	virtual void draw(RenderWindow&)const = 0;
	IntRect getPosition() { return this->m_position; }

protected:
	IntRect m_position;
	Color m_color;
	Texture m_pic;
	int m_numOfDemons;
};

