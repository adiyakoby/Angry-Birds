#pragma once

#include "Window.h"
#include "SFML/Graphics.hpp"
#include "GameResources.h"

class GameController
{
public:
	GameController();
	~GameController();

	//methods
	void runGame();
	void menuManeger();
	//void lvlManeger();



private:
	Window m_window;
	//Menu m_menu;
	//LevelManeger m_lvlmng;
	//std::vector<StaticObject> m_staticObjects;
	//std::vector<Birds> m_staticObjects;
	//std::vector<sf::Music> m_gameMusic;

	//init functions
	//void initObjects();

};

