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
		switch (event.type)
		{
		case sf::Event::Closed:
			m_gameTools->m_window.getWindow().close();
			break;


		case sf::Event::MouseButtonReleased:
		{
			auto location = m_gameTools->m_window.getWindow().mapPixelToCoords(
				{ event.mouseButton.x, event.mouseButton.y });

			m_mode = handleClick(location);
			m_event = true;
			break;
		}
		}
	}
}

void HelpScreenState::update()
{
	if (m_event)
		helpManeger();
}

void HelpScreenState::Draw()
{
	m_gameTools->m_window.getWindow().clear();
	drawHelpScreen();
	m_gameTools->m_window.getWindow().display();
}

void HelpScreenState::initilaize()
{
	m_backGround.setTexture(&GameResources::getInstance().getBackGroundScreens(1));
	m_backGround.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	m_backGround.setPosition(0, 0);

	float delta{ 0 };

	//menu buttuns
	for (size_t i = 0; i < 1; i++)
	{
		m_buttons.emplace_back();
		m_buttons.back().setTexture(&GameResources::getInstance().getHelpTexture(i));
		m_buttons.back().setSize(m_backGround.getSize() * 0.2f);
		m_buttons.back().setOrigin(m_buttons.back().getSize() * 0.5f);
	}
	m_buttons.at(0).setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100);

	//sound buttun
	m_buttons.emplace_back();
	//if(GameResources::getInstance().getMusicStatus() == musicCommand::PAUSE)
	//	m_buttons.back().setTexture(&GameResources::getInstance().getSoundTexture(static_cast<int>(musicCommand::PAUSE)));
	//else 
	//	m_buttons.back().setTexture(&GameResources::getInstance().getSoundTexture(static_cast<int>(musicCommand::PLAY)));
	m_soundButton.setRadius(50.f);
	m_soundButton.setOrigin(m_soundButton.getRadius(), m_soundButton.getRadius());
	m_soundButton.setPosition(WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100);
	setSoundTexture(m_soundButton);
}

helpScreenCommand HelpScreenState::handleClick(const sf::Vector2f& mouse_loc) // getStatus() == sf::Music::Paused
{
	if (m_soundButton.getGlobalBounds().contains(mouse_loc))
		return (GameResources::getInstance().getMusicStatus() == musicCommand::PAUSE ? helpScreenCommand::SOUND : helpScreenCommand::MUTE);

	for (size_t i = 0; i < m_buttons.size(); i++)
		if (m_buttons.at(i).getGlobalBounds().contains(mouse_loc))
			return static_cast<helpScreenCommand>(i);

	return helpScreenCommand::DEFAULT;
}

void HelpScreenState::helpManeger()
{
	switch (m_mode)
	{
	case helpScreenCommand::BACK:     m_gameTools->m_gameStates.removeState();        break;
	case helpScreenCommand::MUTE:;
	case helpScreenCommand::SOUND:    soundButtonClicked(m_soundButton);                               break;
	default:																	      break;
	}
	m_event = false;
}


//void HelpScreenState::setSound(const helpScreenCommand& cmd)
//{
//	if (cmd == helpScreenCommand::MUTE)
//	{
//		GameResources::getInstance().playBackGroundMusic();
//		m_buttons.at(1).setTexture(&GameResources::getInstance().getSoundTexture(static_cast<int>(musicCommand::PAUSE)), true);
//	}
//	else
//	{
//		GameResources::getInstance().playBackGroundMusic();
//		m_buttons.at(1).setTexture(&GameResources::getInstance().getSoundTexture(static_cast<int>(musicCommand::PLAY)), true);
//	}
//
//}

void HelpScreenState::drawHelpScreen()
{
	m_gameTools->m_window.getWindow().draw(m_backGround);
	for (size_t i = 0; i < m_buttons.size(); i++)
		m_gameTools->m_window.getWindow().draw(m_buttons.at(i));
	m_gameTools->m_window.getWindow().draw(m_soundButton);
}


