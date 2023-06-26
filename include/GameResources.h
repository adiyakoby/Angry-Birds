#pragma once

#include <iostream>
#include <vector>
#include <array>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Macro.h"

class GameResources
{
public:
	static GameResources& getInstance();
	GameResources(const GameResources&) = delete; //disable copy constructor
	GameResources operator=(const GameResources&) = delete; //disable assimenget operator

	sf::Texture& getMenuTexture(const int& index);
	sf::Texture& getHelpTexture(const int& index);
	sf::Texture& getBirdTexture(const int& index);
	sf::Texture& getRogatkaTexture(const int& index);
	sf::Texture& getPigsTexture(const int& index);
	sf::Texture& getPoofTexture(const int& index);
	sf::Texture& getLock();
	sf::Texture& getTransitionScreensState(const TransitionScreen&);
	sf::Texture& getObstacleTexture(const int& index);
	sf::Texture& getButtons(const int& index);
	sf::Texture& getLevelsFields(const int& index);
	sf::Texture& getBackGroundScreens(const backGrounds&);

	void playBackGroundMusic();

	musicCommand getMusicStatus() const;
	sf::Font& getFont(const int& index);
	sf::Text& createText(const std::string &, const sf::Color &, const int&);

private:
	//constructor/ distructor
	GameResources();
	~GameResources() = default;

	//members
	sf::Texture m_spriteSheet;
	sf::Texture m_lock;

	std::vector <sf::Texture> m_menuTexture;
	std::vector <sf::Texture> m_helpScreenTexture;//for state
	std::vector <sf::Texture> m_soundTexture;//for state
	std::vector <sf::Texture> m_objectTexture;
	std::vector <sf::Texture> m_backGround;

	std::vector <sf::Texture> m_databuttons;
	std::vector <sf::Texture> m_helpTexture;
	std::vector <sf::Texture> m_birdsTexture;
	std::vector <sf::Texture> m_woodsTexture;
	std::array <sf::Texture,2> m_rogatkaTexture;
	std::vector <sf::Texture> m_groundTexture;
	std::vector <sf::Texture> m_pigsTexture;
	std::vector <sf::Texture> m_poofTexture;
	std::vector <sf::Texture> m_transitionScreensState;
	std::vector <sf::Texture> m_buttons;
	std::vector <sf::Texture> m_obstacles;
	std::vector <sf::Texture> m_levelsFields;
	std::vector <sf::Font> m_font;

	sf::SoundBuffer m_BackGroundBuffer;
	sf::Sound m_BackGroundSound;


	sf::Text m_text;
	
	//func
	void initTextures();
	void initFonts();
	void initSounds();
};