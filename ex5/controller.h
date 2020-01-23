#pragma once
#include <iostream>
#include "Level.h"
#include "Menu.h"

using sf::RenderWindow;
using sf::VideoMode;
using std::move;

class controller
{
public:
	~controller();
	controller(const DataBase&) = delete;
	controller& operator = (const controller&) = delete;
	static controller& instance();
	void run();
	Clock loadClock() { return m_clock; }
	void restartClock() { m_clock.restart(); }

private:
	controller();
	void play(RenderWindow &);
	void gameOver(RenderWindow &, Texture);

	RenderWindow m_window;
	Menu m_menu;
	Player m_pac;
	Level m_level;
	Texture m_youWin;
	Texture m_youLost;
	Clock m_clock;

};


