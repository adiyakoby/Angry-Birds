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
	int levelToRead = 0;
	int score;
	std::string levelStatus;
};

class LevelSelectState : public State
{
public:
	LevelSelectState(std::shared_ptr<GameTools>);
	~LevelSelectState() = default;
	void processManeger();
	void update();
	void Draw();
	void Resume()override;
	void Pause()override {}

	void levelRequest();//set play data( e.g. which level to read)
	void updateReturningValue();//get the returning value from play state
	void openNewLevel();
	void drawLevelSelect();
	int handleClick(sf::Vector2f);
	void setSound();
protected:
	void initilaize();
private:
	std::shared_ptr<SharedData> m_sharedData;
	std::shared_ptr<GameTools> m_gameTools;
	std::vector<std::pair<sf::RectangleShape, sf::Text>> m_levelsFields;
	std::vector<sf::CircleShape> m_Buttons;
	std::vector<std::pair<std::string, int>> m_levelData;
	sf::RectangleShape m_backGround;
	int m_requestedLevel;
	bool m_event;
	bool m_firstPlay;
	sf::Sound m_music;
};

