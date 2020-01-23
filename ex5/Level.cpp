#include "stdafx.h"
#include "Level.h"
#include "controller.h"

//defines
const sf::Color RED = Color(255, 187, 187);
const sf::Color GREEN = Color(90, 241, 10);
const sf::Color BLUE = Color(0, 169, 251);
const sf::Color CLEAR = Color(255, 255, 255);

//level c-tor
Level::Level(Player& pac)
	: m_pac(pac),m_file(DataBase::instance().loadLevelNames())
{
	//make vector with level names
	string name;
	while (!m_file.eof()) {
		getline(m_file, name);
		m_names.push_back(name);
	}
	srand(static_cast <unsigned int> (time(NULL)));
}

Level::~Level()
{
}

//read level from file
void Level::readLevel(int levelNum)
{
	char c;
	IntRect position;
	Vector2i size;

	m_file.close();
	m_file.open(m_names[levelNum]);
	m_file >> size.x >> size.y;

	for (int i = 0; i < size.x && m_file.get(c); i++)
		for (int j = 0; j < size.y && m_file.get(c); j++) {

			position = { j * 70, i * 70 , 70, 70 };

			//initialize objects
			switch (c) {
			case '@':
				initPac(position, RED);
				break;
			case '%':
				initDemon(position, RED);
				break;
			case '#':
				initWall(position, RED);
				break;
			case '*':
				initCookie(position, RED);
				break;
			case 'W':
				initPac(position, GREEN);
				break;
			case 'T':
				initDemon(position, GREEN);
				break;
			case 'E':
				initWall(position, GREEN);
				break;
			case 'I':
				initCookie(position, GREEN);
				break;
			case 'S':
				initPac(position, BLUE);
				break;
			case 'G':
				initDemon(position, BLUE);
				break;
			case 'D':
				initWall(position, BLUE);
				break;
			case 'K':
				initCookie(position, BLUE);
				break;
			}
		}
	m_pac.setNumOfDemons(m_demon.size());
	m_file.close();
}

// initialize pacman
void Level::initPac(IntRect position, Color color) {

	Texture pic = DataBase::instance().loadPic(PAC);
	m_pac.levelData(position, color, pic);
}

// initialize demon
void Level::initDemon(IntRect pos, Color color)
{
	TypePic type;
	Texture pic;

	if (color == RED)
		type = DEMON1;
	if (color == GREEN)
		type = DEMON2;
	if (color == BLUE)
		type = DEMON3;

	pic = DataBase::instance().loadPic(type);

	if ((bool)(rand() % 2))
		m_demon.push_back((make_unique<Smart>)(pos, CLEAR, pic, m_pac));
	else
		m_demon.push_back((make_unique<Random>)(pos, CLEAR, pic));
}

// initialize cookie
void Level::initCookie(IntRect pos, Color color)
{
	CookieType type;
	Texture pic = DataBase::instance().loadPic(COOKIE);

	if (color == RED)
		type = REGULAR;
	if (color == GREEN)
		type = HEALTH;
	if (color == BLUE)
		type = POISON;

	m_board.setObject(make_unique<Cookie>(pos, color, pic, type));
	m_board.increaseCookie();
}

// initialize wall
void Level::initWall(IntRect pos, Color color) {

	Texture pic = DataBase::instance().loadPic(WALL);
	m_board.setObject(make_unique<Wall>(pos, color, pic));

}

//draw the board and dynamic object to the  window
void Level::draw(RenderWindow &window) const
{
	m_board.draw(window);
	m_pac.draw(window);

	for (unsigned i = 0; i < m_demon.size(); i++)
		m_demon[i]->draw(window);
}


void Level::run(RenderWindow & window)
{
	Event event;
	controller::instance().restartClock();

	while (window.isOpen() && m_pac.isAlive()) {

		if (!play())
			return;

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

				switch (event.key.code) {

				case Keyboard::Up:
					m_pac.setDirection(UP);
					break;
				case Keyboard::Down:
					m_pac.setDirection(DOWN);
					break;
				case Keyboard::Right:
					m_pac.setDirection(RIGHT);
					break;
				case Keyboard::Left:
					m_pac.setDirection(LEFT);
					break;
				case Keyboard::Space:
					m_pac.setDirection(STOP);
					break;
				}
			}
		}
		draw(window);
		window.display();
	}
}

bool Level::play()
{
	m_pac.move(m_clock.getElapsedTime().asSeconds());

	//Collision between pacman to static object
	if (m_board.checkCollision(m_pac))
		if (m_board.getCookieCounter() == 0) {
			m_demon.clear();
			m_pac.increaseLevel();
			return false;
		}

	//Collision between demon to static object
	for (size_t i = 0; i < m_demon.size(); i++) {
		m_board.checkCollision(*m_demon[i]);
		m_demon[i]->move(m_clock.getElapsedTime().asSeconds());

		//Collision between demon to pacman
		if (m_board.checkCollision(m_pac, *m_demon[i]))
			resetDemons();

	}
	return true;
	
}

void Level::resetDemons()
{
	for (size_t i = 0; i < m_demon.size(); i++)
		m_demon[i]->collideWith(m_pac);
}
