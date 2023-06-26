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

	sf::Texture& getMenuTexture(int index);
	sf::Texture& getHelpTexture(int index);
	sf::Texture& getBirdTexture(int index);
	sf::Texture& getWoodsTexture(int index);
	sf::Texture& getRogatkaTexture(int index);
	sf::Texture& getPigsTexture(int index);
	sf::Texture& getPoofTexture(int index);
	sf::Texture& getLock();
	sf::Texture& getTransitionScreensState(const TransitionScreen&);
	sf::Texture& getObstacleTexture(const int& index);
	sf::Texture& getButtons(int index);
	sf::Texture& getLevelsFields(int index);
	sf::Texture& getBackGroundScreens(const backGrounds&);

	void playBackGroundMusic();

	musicCommand getMusicStatus() const;
	sf::Font& getFont(int index);
	sf::Text& createText(std::string, sf::Color, int);

private:
	//constructor/ distructor
	GameResources();
	~GameResources() = default;

	//members
	sf::Texture m_spriteSheet;
	sf::Texture m_lock;

	std::array <sf::Texture, 3> m_menuTexture;
	std::array <sf::Texture, 4> m_helpScreenTexture;//for state
	std::array <sf::Texture,3> m_backGround;
	std::array <sf::Texture,4> m_birdsTexture;
	std::array <sf::Texture,2> m_rogatkaTexture;
	std::array <sf::Texture, 2> m_pigsTexture;
	std::array <sf::Texture, 5> m_poofTexture;
	std::array <sf::Texture, 2> m_transitionScreensState;
	std::array <sf::Texture, 5> m_buttons;
	std::array <sf::Texture, 18> m_obstacles;
	std::array <sf::Texture, 6> m_levelsFields;
	std::array <sf::Font, 2> m_font;

	sf::SoundBuffer m_BackGroundBuffer;
	sf::Sound m_BackGroundSound;


	sf::Text m_text;
	
	//func
	void initTextures();
	void initFonts();
	void initSounds();
};