#include "stdafx.h"
#include "controller.h"

int const LENGTH_WINDOW = 1450;
int const WIDTH_WINDOW = 1000;

//defult c-tor
controller::controller()
	:m_level(m_pac),
	m_youLost(DataBase::instance().loadPic(LOST)),
	m_youWin(DataBase::instance().loadPic(WIN))
{
	//create the game of the window
	m_window.create(VideoMode(LENGTH_WINDOW, WIDTH_WINDOW),
		"Pacman", sf::Style::Titlebar | sf::Style::Close);
}

//game over control
void controller::gameOver(RenderWindow &window,Texture end)
{
	Event event;
	Sprite sp;
	sp.setTexture(end);

	while (m_window.isOpen()) {

		window.draw(sp);

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape)
					window.close();
				break;
			}
		}
		window.display();
	}
}

//opens and reads the different levels
void controller::play(RenderWindow &window)
{
	do {
		m_level.readLevel(m_pac.getLevel() - 1);
		m_level.run(m_window);

		if (m_pac.getLevel() == 5 && m_pac.isAlive()) {
			gameOver(m_window, m_youWin);
			return;
		}
	} while (m_pac.isAlive());
	
	gameOver(m_window,m_youLost);
}

controller::~controller()
{
}

//for singelton
controller & controller::instance()
{
	static controller inst;
	return inst;
}
//runs the game by request of user
void controller::run()
{
	TypeButton button;

	while (m_window.isOpen()) {

		while (m_menu.run(m_window, button));

		switch (button) {

		case PLAY:
			play(m_window);
			return;
		case HELP:
			while (m_menu.helpSelection(m_window));
			break;
		case EXIT:
			m_window.close();
			break;
		default:
			break;
		}

	}

}
