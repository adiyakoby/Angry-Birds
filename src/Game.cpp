#include "Game.h"

Game::Game()
	:m_gameTools(std::make_shared<GameTools>())
{
	//m_gameTools->gameStates.AddState(mainMenuState(this -> m_gameTools));//create the first state of the game - the menu
}

void Game::runGame()
{
	//in each iteration process according to the state
	while (m_gameTools->m_window.isOpen())
	{
		//m_gameTools->stateMachine.checkForUpdates();
		//m_gameTools->stateMachine.getCurrentState.processManeger();
		//m_gameTools->stateMachine.getCurrentState.update();
		//m_gameTools->stateMachine.getCurrentState.Draw();
	}
}
