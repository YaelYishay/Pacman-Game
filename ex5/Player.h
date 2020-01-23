#pragma once
#include "DataBase.h"
#include "DynamicObject.h"
#include "Cookie.h"

using std::to_string;
using sf::Text;
using sf::Keyboard;
using sf::Event;
using sf::Sprite;
using sf::Clock;

class Player :public DynamicObject
{
public:
	Player();
	~Player();

	virtual bool collideWith(Object&);
	virtual bool collideWith(Demon&);
	virtual bool collideWith(Player&);
	virtual bool collideWith(Wall&);
	virtual bool collideWith(Cookie&);

	void draw(RenderWindow &)const;
	void move(float);
	void increaseLevel();
	int getLevel();
	bool isAlive();
	void levelData(IntRect, Color, Texture);

private:
	void setPosition(IntRect);
	vector<unique_ptr<Text>> m_data;
	Font m_dataFont;
	int m_lives;
	int m_score;
	int m_level;
	float m_speed;
};