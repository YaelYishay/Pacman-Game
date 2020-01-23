#pragma once
#include "Smart.h"
#include "Random.h"
#include "Board.h"
#include "DataBase.h"
#include "Demon.h"
#include "Wall.h"
#include "Cookie.h"

using sf::Text;
using std::string;
using std::rand;
using sf::Event;
using sf::Keyboard;
using sf::Clock;
using sf::seconds;

class Level
{
public:
	Level(Player&);
	~Level();
	void readLevel(int); //read file
	void run(RenderWindow &); //level loop

private:
	void draw(RenderWindow &)const; //draw board and Characters
	void initPac(IntRect, Color);  // initialize pacman
	void initDemon(IntRect, Color); // initialize demon
	void initCookie(IntRect, Color); // initialize cookie
	void initWall(IntRect, Color); // initialize wall
	bool play(); //Collisions and movement
	void resetDemons(); //reset demon position

	Player& m_pac;
	ifstream &m_file;
	vector<string> m_names;
	Board m_board;
	vector<unique_ptr<Demon>> m_demon;
	Clock m_clock;
};

