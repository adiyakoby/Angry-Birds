#pragma once

#include "Macro.h"
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
#include "LevelManager.h"
#include "BlueBird.h"

struct poof {

	poof(const sf::Vector2f& pos) : m_pos{pos} { ; }
	sf::Vector2f m_pos;
	sf::Clock m_clock;
	sf::Time elapsedTime() { return m_clock.getElapsedTime(); };
};

struct SharedData;

class PlayState :public State
{
public:
	PlayState(std::shared_ptr<GameTools>, std::shared_ptr<SharedData>);
	~PlayState() = default;

	void processManeger();
	void update();
	void Draw();
	void Resume()override;
	void Pause()override {}

	//update func
	void deleteObj();
	void drawGame();
	void updateView();
	void setNextBird(const bool &x);
	void setUpForEndLevel(std::string);
	//void setUpForGameOver();
	bool levelEnd();
	bool isFinishedMoving();
	void updateDataPosition();
	void setScore(int);
	
protected:
	void initilaize();
	
private:
	std::shared_ptr<GameTools> m_gameTools;
	std::vector<sf::RectangleShape> m_buttons;
	sf::RectangleShape m_backGround;
	menuCommand m_mode;
	int m_level;
	sf::Sound m_music;

	//LevelManeger m_lvlmng;
	std::array<std::unique_ptr<StaticObjects>, 2> m_worldObjects;
	std::vector<std::unique_ptr<Bird>> m_birds;
	std::vector<std::unique_ptr<StaticObjects>> m_pigs;
	std::vector<std::unique_ptr<StaticObjects>> m_gameObjects;
	std::vector<std::pair<sf::Text, sf::Text>> m_levelData;
	sf::RectangleShape m_background;
	std::unique_ptr<MyContactListener> m_contactListener;
	//std::vector<sf::Music> m_gameMusic;
	

	//destroy's animation array
	std::array<sf::RectangleShape, 3> m_destroyAnimation;
	std::vector<poof>m_poofsContainer;
	//init functions
	std::shared_ptr<World> m_world;
	std::shared_ptr<SharedData> m_sharedData;
	LevelManager m_lvlsMngr;
	void drawDestroyedObj();
	//init funcs
	void createGroundAndRogatka();
	void createGameObjs();
	void createLevelData();
};


