#pragma once

#include "Macro.h"
#include <SFML/Graphics.hpp>

struct GameTools
{
	//members
	//StateMachine m_gameStates;
	sf::RenderWindow m_window;

	//constructor
	GameTools()
		:m_window{ sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Angry Birds" }
	{
		m_window.setFramerateLimit(40);
	}

};

class Game
{
public:
	Game();
	~Game() = default;
	void runGame();
private:
	std::shared_ptr<GameTools> m_gameTools;
};

