#pragma once

#include "Macro.h"
#include "StateMachine.h"
#include "Window.h"
#include "GameResources.h"


#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

struct GameTools
{
	//members
	StateMachine m_gameStates;
	Window m_window;
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

