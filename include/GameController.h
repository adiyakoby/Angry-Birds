#pragma once

#include "Window.h"
#include "Menu.h"
#include "GameResources.h"
#include "Bird.h"
#include <memory>
#include "Ground.h"
#include <box2d/box2d.h>
#include "World.h"
#include "Wood.h"
#include "Rogatka.h"

class GameController
{
public:
	GameController();
	~GameController() = default;

	//methods
	void runGame();
	void menuManeger(const menuCommand&);
	void drawGame();
	//void lvlManeger();



private:
	Window m_window;
	bool m_menuMode;
	Menu m_menu;
	//Try temporary world
	std::unique_ptr<World> m_world;

	//LevelManeger m_lvlmng;
	//std::vector<StaticObject> m_staticObjects;
	//std::vector<Birds> m_staticObjects;
	//std::vector<sf::Music> m_gameMusic;

	//init functions
	//void initObjects();
	void initWorld();

};

