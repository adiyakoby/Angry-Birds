#pragma once

#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>


#include "Macro.h"
#include "State.h"
#include "Game.h"

//struct that holds information that need to shared between the states:
//1)LevelSelectState 2)PlayState 3)TransnitionScreen
struct SharedData
{
	int levelToRead;
	int score;
	GameStates currentState;
};

class LevelSelectState : public State
{
public:
	LevelSelectState(std::shared_ptr<GameTools>);
	~LevelSelectState() = default;
	void processManeger();
	void update();
	void Draw();

	void levelRequest(int);
	void drawLevelSelect();
protected:
	void initilaize();
private:
	std::shared_ptr<SharedData> m_sharedData;
	std::shared_ptr<GameTools> m_gameTools;
	std::vector<sf::RectangleShape> m_levelsFields;
	sf::RectangleShape m_backButton;
	std::vector<std::pair<std::string, int>> m_levelData;
	sf::RectangleShape m_backGround;
	bool m_event;
	sf::Sound m_music;
};

