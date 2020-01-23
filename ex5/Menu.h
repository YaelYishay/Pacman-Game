#pragma once
#include "DataBase.h"

using sf::RenderWindow;
using sf::Sprite;
using sf::IntRect;
using sf::Event;
using sf::Keyboard;
using sf::Mouse;
using sf::Vector2f;


enum TypeButton { PLAY, HELP, EXIT };

class Menu
{
public:
	Menu();
	~Menu();
	void draw(RenderWindow&);
	bool click(Event, TypeButton&);
	bool run(RenderWindow&, TypeButton&);
	bool helpSelection(RenderWindow& );

private:
	void showSelection(RenderWindow&, Event);

	vector<unique_ptr<IntRect>> m_button;
	Texture m_menu; // background menu screen
	Texture m_help; // background help screen
	Texture m_mouse;
	Sound m_elmo;
};

