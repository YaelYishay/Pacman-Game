#pragma once
#include <iostream>
#include "DataBase.h"
#include "Demon.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include <cmath>

using sf::Vector2i;
using std::cin;
using sf::IntRect;
using sf::Color;
using sf::Sprite;

class Board
{
public:
	Board();
	~Board();
	void draw(RenderWindow &)const;
	void setObject(unique_ptr<StaticObject> s);
	bool checkCollision(DynamicObject&,DynamicObject&) const;
	bool checkCollision(DynamicObject&);
	void increaseCookie();
	int getCookieCounter() const;

private:
	vector<unique_ptr<StaticObject>> m_StaticObject;
	Texture m_pic;
	Font m_font;
	Text m_data;
	int m_cookieCounter;
};

