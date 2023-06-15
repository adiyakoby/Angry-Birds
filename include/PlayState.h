#pragma once

#include "Game.h"
#include "Bird.h"
#include "Ground.h"
#include "World.h"
#include "Wood.h"
#include "Rogatka.h"
#include "MyContactListener.h"
#include "Pig.h"
#include "YellowBird.h"
#include "RedBird.h"

class PlayState :public State
{
public:
	PlayState(std::shared_ptr<GameTools>);
	~PlayState() = default;

	void processManeger();
	void update();
	void Draw();

	void drawGame();
	void createBirds();
	void createBuilding();
	void createGroundAndRogatka();
	void createPigs();
protected:
	void initilaize();

private:
	std::shared_ptr<GameTools> m_gameTools;
	std::vector<sf::RectangleShape> m_buttons;
	sf::RectangleShape m_backGround;
	menuCommand m_mode;
	bool m_event;
	sf::Sound m_music;

	//Try temporary world
	World m_world;

	//LevelManeger m_lvlmng;
	std::array<std::unique_ptr<StaticObjects>, 2> m_staticObjects;
	std::vector<std::unique_ptr<Bird>> m_birds;
	std::vector<std::unique_ptr<StaticObjects>> m_building;
	std::vector<std::unique_ptr<StaticObjects>> m_pigs;
	sf::RectangleShape m_background;
	std::unique_ptr<MyContactListener> m_contactListener;
	//std::vector<sf::Music> m_gameMusic;
	//init functions
};


