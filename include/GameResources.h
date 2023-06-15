#pragma once

#include <iostream>

#include <vector>
#include <array>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//enum class menuCommand { PLAY, HELP, EXIT, BACK, SOUND, MUTE, DEFAULT};


#include <SFML/audio.hpp>
class GameResources
{
public:
	static GameResources& getInstance();
	GameResources(const GameResources&) = delete;//disable copy constructor
	GameResources operator=(const GameResources&) = delete;//disable assimenget operator
	sf::Texture& getMenuTexture(int index);
	sf::Texture& getHelpTexture(int index);//state
	sf::Texture& getSoundTexture(int index);//state
	sf::Texture& getBirdTexture(int index);
	sf::Texture& getWoodsTexture(int index);
	sf::Texture& getRogatkaTexture(int index);
	sf::Texture& getGroundTexture(int index);
	sf::Texture& getPigsTexture(int index);

	/*sf::Texture& getObjectTexture(int index);
	sf::Texture& getDataButtuns(int index);*/
	sf::Texture& getTransitionScreens(int index);
	sf::SoundBuffer& Playaffect(int index);
	/*sf::Font& getFont(int index);
	
	sf::Text& createText(std::string, sf::Vector2f, sf::Color, int);*/
private:
	//constructor/ distructor
	GameResources();
	~GameResources() = default;

	//members
	sf::Texture m_spriteSheet;
	std::vector <sf::Texture> m_menuTexture;
	std::vector <sf::Texture> m_helpScreenTexture;//for state
	std::vector <sf::Texture> m_soundTexture;//for state
	std::vector <sf::Texture> m_objectTexture;
	std::vector <sf::Texture> m_transitionScreens;
	std::vector <sf::Texture> m_databuttons;
	std::vector <sf::Texture> m_helpTexture;
	std::vector <sf::Texture> m_birdsTexture;
	std::vector <sf::Texture> m_woodsTexture;
	std::vector<sf::Texture> m_rogatkaTexture;
	std::vector<sf::Texture> m_groundTexture;
	std::vector<sf::Texture> m_pigsTexture;

	std::vector <sf::Font> m_font;
	std::vector <sf::SoundBuffer> m_affects;

	sf::Sound m_affect;
	sf::Text m_text;
	//func
	void initTextures();
	//void initFonts();
	void initSounds();
};