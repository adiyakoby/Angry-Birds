#include "Game.h"
#include "HelpScreenState.h"
#include<memory>
Game::Game()
	:m_gameTools(std::make_shared<GameTools>())
{
	m_gameTools->m_gameStates.addState(std::make_unique<HelpScreenState>(this -> m_gameTools), true);//create the first state of the game - the menu
}

void Game::runGame()
{
	//in each iteration process according to the state
	while (m_gameTools->m_window.isOpen())
	{
		m_gameTools->m_gameStates.checkForUpdates();
		m_gameTools->m_gameStates.getCurrentState()->processManeger();
		m_gameTools->m_gameStates.getCurrentState()->update();
		m_gameTools->m_gameStates.getCurrentState()->Draw();
	}
}
