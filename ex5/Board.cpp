#include "stdafx.h"
#include "Board.h"

//defult c-tor
Board::Board()
	:m_pic(DataBase::instance().loadPic(BOARD)),
	m_font(DataBase::instance().loadFont(FONT)),
	m_data("Score:            Lives:           Level:    ", m_font, 40),
	m_cookieCounter(0)
{
	m_data.setFillColor(Color::White);
	m_data.setPosition(10, 10);
}

Board::~Board()
{
}

//draw the board to the window
void Board::draw(RenderWindow & window) const
{
	Sprite sp;
	sp.setTexture(m_pic);
	window.draw(sp);

	//draw each of the static objects on the board
	for (unsigned i = 0; i < m_StaticObject.size(); i++)
		m_StaticObject[i]->draw(window);

	window.draw(m_data);
}

//add a static object to the board
void Board::setObject(unique_ptr<StaticObject> s) {
	m_StaticObject.push_back(std::move(s));
}

//check if their has been a collision between a pac and demon
bool Board::checkCollision(DynamicObject &pac, DynamicObject &otherdynamic) const
{
	if (pac.getPosition().intersects(otherdynamic.getPosition())) {
		otherdynamic.collideWith(pac);
		pac.collideWith(otherdynamic);
		return true;
	}
	return false;
}

//check if the pac has collected a cookie of collided with a wall
bool Board::checkCollision(DynamicObject &dynamic)
{
	for (size_t i = 0; i < m_StaticObject.size(); i++)
		if (dynamic.getPosition().intersects(m_StaticObject[i]->getPosition())) {

			//if the pac has collected a cookie
			if (m_StaticObject[i]->collideWith(dynamic)){
					m_StaticObject.erase(m_StaticObject.begin() + i);
					m_cookieCounter--;

					if (m_cookieCounter == 0)
						m_StaticObject.clear();
				
			}
			return true;
		}
	return false;
}

//update the cookie counter
void Board::increaseCookie(){
	m_cookieCounter++;
}

//get how many cookies are on the board
int Board::getCookieCounter() const{
   return m_cookieCounter;
}









