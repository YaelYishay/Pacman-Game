#pragma once
#include "StaticObject.h"
#include "DataBase.h"

using sf::Clock;

enum CookieType {
	HEALTH, REGULAR, POISON
};

class Cookie :public StaticObject
{
public:
	Cookie(IntRect, Color, Texture, CookieType);
	~Cookie();
	void draw(RenderWindow &) const override;
	virtual bool collideWith(Object&);
	virtual bool collideWith(Demon&);
	virtual bool collideWith(Player&);
	virtual bool collideWith(Wall&);
	virtual bool collideWith(Cookie&);

	void cookieEffect(float& speed) const;

private:
	CookieType m_type;
};

