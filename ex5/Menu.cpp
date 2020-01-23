#include "stdafx.h"
#include "Menu.h"

const int BUTTON_POSITION = 3;

//c-tor
Menu::Menu()
	:m_menu(DataBase::instance().loadPic(MENU)),
	m_help(DataBase::instance().loadPic(HELP_PIC)),
	m_mouse(DataBase::instance().loadPic(MOUSE))

{
	for (size_t i = 0; i < 3; i++)
		m_button.push_back(make_unique<IntRect>(1000, i * 160 + 490, 325, 100));
	m_button.push_back(make_unique<IntRect>(120, 722, 320, 827));
}

Menu::~Menu()
{
}

//display to window
void Menu::draw(RenderWindow &window)
{
	Sprite sp;
	sp.setTexture(m_menu);
	window.draw(sp);
}

//check if menu option has been selected
bool Menu::click(Event event, TypeButton& button)
{
	for (size_t i = 0; i < 3; i++)
		if (m_button[i]->contains(event.mouseButton.x, event.mouseButton.y)) {
			button = (TypeButton)i;
			return true;
		}
	return false;
}

//run the selected button function
bool Menu::run(RenderWindow & window, TypeButton& button)
{
	Event event;

	while (window.isOpen()) {

		window.clear();
		draw(window);

		if (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::MouseMoved:
				showSelection(window, event);
				break;
			case Event::MouseButtonReleased:
				if (click(event, button)) {
					m_elmo.setBuffer(DataBase::instance().getSound());
					m_elmo.play();
					return false;
				}
				break;
			case Event::Closed:
				window.close();
				break;
			case Keyboard::Escape:
				window.close();
				break;
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape)
					window.close();
				break;
			default:
				break;
			}
			window.display();
		}
	}
	return true;
}

//help function
bool Menu::helpSelection(RenderWindow &window) 
{
	Event event;
	Sprite sp;
	window.setMouseCursorVisible(true);


	while (window.isOpen()) {

		window.clear();
		sp.setTexture(m_help);
		window.draw(sp);

		if (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::MouseMoved:
				break;
			case Event::Closed:
				window.close();
				break;
			case Keyboard::Escape:
				window.close();
				break;
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape)
					window.close();
				break;
			case Event::MouseButtonReleased:
				if (m_button[BUTTON_POSITION]->contains(event.mouseButton.x, event.mouseButton.y)) {

				return false;
				}
				break;
			default:
				break;
			}
			window.display();
		}
	}
	return true;
}

//accent menu selection function
void Menu::showSelection(RenderWindow& window, Event event)
{
	sf::RectangleShape underline;
	underline.setSize({300.f, 2.f});
	Sprite sp;
	sp.setTexture(m_mouse);
	window.setMouseCursorVisible(true);

	for (size_t i = 0; i < 3; i++)

		if (m_button[i]->contains(event.mouseMove.x, event.mouseMove.y)) {
			underline.setPosition(m_button[i]->left, m_button[i]->top + m_button[i]->height+2);
			window.setMouseCursorVisible(false);
			sp.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));
			window.draw(sp);
			window.draw(underline);
		}

}


