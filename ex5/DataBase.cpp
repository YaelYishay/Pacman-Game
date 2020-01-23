#include "stdafx.h"
#include "DataBase.h"

//singelton c-tor
DataBase::DataBase()
	:m_levelNames("levelNames.txt")
{
	//get textures
	for (int i = 0; i < 12; i++)
		m_texture.push_back(make_unique<Texture>());

	m_texture[0]->loadFromFile("pic/Demon1.png");
	m_texture[1]->loadFromFile("pic/Demon2.png");
	m_texture[2]->loadFromFile("pic/Demon3.png");
	m_texture[3]->loadFromFile("pic/background.png");
	m_texture[4]->loadFromFile("pic/pacman.png");
	m_texture[5]->loadFromFile("pic/cookie.png");
	m_texture[6]->loadFromFile("pic/Wall.png");
	m_texture[7]->loadFromFile("pic/background2.png");
	m_texture[8]->loadFromFile("pic/background3.jpg");
	m_texture[9]->loadFromFile("pic/mouse.png");
	m_texture[10]->loadFromFile("pic/YOU WIN.png");
	m_texture[11]->loadFromFile("pic/YOU LOST.png");

	//get fonts
	m_font.loadFromFile("font.ttf");

	//get sounds
	m_music.openFromFile("theme.ogg");
	m_music.setLoop(true);
	m_music.setVolume(50.f);
	m_music.play();

	m_buff.loadFromFile("elmo.wav");
}

DataBase::~DataBase()
{
}

//for singleton
DataBase& DataBase::instance()
{
	static DataBase inst;
	return inst;
}

//get a texture
Texture& DataBase::loadPic(TypePic type){
	return *m_texture[type];
}

//get a font
Font & DataBase::loadFont(TypePic font)
{
	return m_font;
}

//get the level names file
ifstream& DataBase::loadLevelNames(){
	return m_levelNames;
}
