#include "HelpScreenState.h"

HelpScreenState::HelpScreenState(std::shared_ptr<GameTools> gameTools)
	:m_gameTools(gameTools)
{
	initilaize();
}

void HelpScreenState::processManeger()
{
	if (auto event = sf::Event{}; m_gameTools->m_window.getWindow().pollEvent(event))
	{
		;
	}
}

void HelpScreenState::update()
{
}

void HelpScreenState::Draw()
{
	
	//for (auto i : m_bottuns)
	//	m_gameTools->m_window.draw(i);
}

void HelpScreenState::initilaize()
{
}


