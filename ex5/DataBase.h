#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <memory>
#include <iostream>
#include <SFML/Audio/Music.hpp>
#include <SFML\Audio\Sound.hpp>
#include <SFML\Audio\SoundBuffer.hpp>

using sf::SoundBuffer;
using std::string;
using sf::Font;
using std::unique_ptr;
using std::make_unique;
using sf::Texture;
using std::ifstream;
using std::vector;
using sf::Music;
using sf::Sound;


enum TypePic { DEMON1, DEMON2, DEMON3, MENU, PAC, COOKIE, WALL, 
	           BOARD, HELP_PIC ,MOUSE, WIN, LOST, FONT };

class DataBase
{
public:
	~DataBase();
	DataBase(const DataBase&) = delete;
	DataBase& operator = (const DataBase&) = delete;
	static DataBase& instance();
	Texture& loadPic(TypePic);
	Font& loadFont(TypePic);
	ifstream& loadLevelNames();
	SoundBuffer& getSound() { return m_buff; }

private:

	DataBase();
	vector<string>m_names;
	vector<unique_ptr<Texture>>m_texture;
	ifstream m_levelNames;
	Font m_font;
	Music m_music;
	SoundBuffer m_buff;

};

