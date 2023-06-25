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
	sf::Texture& getHelpTexture(int index);//state
	sf::Texture& getSoundTexture(int index);//state
	sf::Texture& getBirdTexture(int index);
	sf::Texture& getWoodsTexture(int index);
	sf::Texture& getRogatkaTexture(int index);
	sf::Texture& getPigsTexture(int index);
	sf::Texture& getPoofTexture(int index);
	sf::Texture& getLock();
	sf::Texture& getTransitionScreensState(int index);
	sf::Texture& getObstacleTexture(const int& index);
	sf::Texture& getButtons(int index);
	sf::Texture& getLevelsFields(int index);
	sf::Texture& getBackGroundScreens(int index);
	void PlayAffect(const gameSounds&);
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
	std::vector <sf::Texture> m_menuTexture;
	std::vector <sf::Texture> m_helpScreenTexture;//for state
	std::vector <sf::Texture> m_soundTexture;//for state
	std::vector <sf::Texture> m_objectTexture;
	std::vector <sf::Texture> m_backGround;
	std::vector <sf::Texture> m_databuttons;
	std::vector <sf::Texture> m_helpTexture;
	std::vector <sf::Texture> m_birdsTexture;
	std::vector <sf::Texture> m_woodsTexture;
	std::vector <sf::Texture> m_rogatkaTexture;
	std::vector <sf::Texture> m_groundTexture;
	std::vector <sf::Texture> m_pigsTexture;
	std::vector <sf::Texture> m_poofTexture;
	sf::Texture m_lock;
	std::vector <sf::Texture> m_transitionScreensState;
	std::vector <sf::Texture> m_buttons;

	std::vector<sf::Texture> m_obstacles;

	std::vector <sf::Texture> m_levelsFields;
	std::vector <sf::Font> m_font;
	std::vector <sf::SoundBuffer> m_gameSounds;
	sf::Sound m_gameMusic;
	sf::Sound m_affect;
	sf::Text m_text;
	
	//func
	void initTextures();
	void initFonts();
	void initSounds();
};