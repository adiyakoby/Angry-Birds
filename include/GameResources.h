#pragma once

#include <iostream>

#include <vector>
#include <array>

#include <SFML/Graphics.hpp>


enum class menuCommand { PLAY, HELP, EXIT, BACK, SOUND };


#include <SFML/audio.hpp>
class GameResources
{
public:
	static GameResources& getInstance();
	GameResources(const GameResources&) = delete;//disable copy constructor
	GameResources operator=(const GameResources&) = delete;//disable assimenget operator
	sf::Texture& getMenuTexture(int index);
	/*sf::Texture& getObjectTexture(int index);
	sf::Texture& getDataButtuns(int index);
	sf::Texture& getTransitionScreens(int index);*/
	/*sf::Font& getFont(int index);
	sf::Sound& Playaffect(int index);
	sf::Text& createText(std::string, sf::Vector2f, sf::Color, int);*/
private:
	//constructor/ distructor
	GameResources();
	~GameResources() = default;

	//members
	std::vector <sf::Texture > m_menuTexture;
	std::vector <sf::Texture > m_objectTexture;
	std::vector <sf::Texture > m_transitionScreens;
	std::vector <sf::Texture > m_databuttons;
	std::vector <sf::Font> m_font;
	std::vector <sf::SoundBuffer> m_affects;

	sf::Sound m_affect;
	sf::Text m_text;
	//func
	void initTextures();
	//void initFonts();
	//void initSounds();
};