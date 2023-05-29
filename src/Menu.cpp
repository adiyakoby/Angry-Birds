#include "Menu.h"

Menu::Menu()
	:m_helpScreen(false) 
{
	m_music.setBuffer(GameResources::getInstance().Playaffect(0));
	m_music.setLoop(true);
	m_music.play();
	
	initButtons();
};

void Menu::drawMenu(sf::RenderWindow& window)
{
	if (m_helpScreen)
	{
		window.draw(m_backGround);
		window.draw(m_buttons.at(3));
	}
	else {
		window.draw(m_backGround);
		for (size_t i = 0; i < m_buttons.size()-2 ; i++)
			window.draw(m_buttons.at(i));
	}

	window.draw(m_buttons.at(4));
	
}
void Menu::setHelp(const bool& x)
{
	m_helpScreen = x;

	if (x) 
		m_backGround.setTexture(&GameResources::getInstance().getTransitionScreens(1), true);
	else m_backGround.setTexture(&GameResources::getInstance().getTransitionScreens(0) , true);
}

menuCommand Menu::handleClick(const sf::Vector2f& mouse_loc) // getStatus() == sf::Music::Paused
{ 
	if (m_buttons.at(4).getGlobalBounds().contains(mouse_loc)) return (m_music.getStatus() == sf::Music::Paused ? menuCommand::SOUND : menuCommand::MUTE);
	if (m_helpScreen) return (m_buttons.at(3).getGlobalBounds().contains(mouse_loc) ? menuCommand::BACK : menuCommand::DEFAULT);
	
	for (size_t i = 0; i < m_buttons.size()-2 ; i++)
		if (m_buttons.at(i).getGlobalBounds().contains(mouse_loc))
			return static_cast<menuCommand>(i);

	return menuCommand::DEFAULT;
}

void Menu::initButtons()
{
	m_backGround.setTexture(&GameResources::getInstance().getTransitionScreens(0));
	m_backGround.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	m_backGround.setPosition(0, 0);

	float delta{ 0 };
	
	//  "play.png", "help.png",  "exit.png" ,"back.png","sound.png", "mute.png"",
	for (size_t i = 0; i < 5; i++)
	{
		m_buttons.emplace_back();
		m_buttons.back().setTexture(&GameResources::getInstance().getMenuTexture(i));
		m_buttons.back().setSize(m_backGround.getSize() * 0.2f);
		m_buttons.back().setOrigin(m_buttons.back().getSize() * 0.5f);
		m_buttons.back().setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 0.4 + delta);
		delta += m_backGround.getSize().x * 0.12f;
	}

	m_buttons.at(3).setPosition(m_buttons.at(2).getPosition());
	m_buttons.at(4).setSize(m_backGround.getSize() * 0.12f);
	m_buttons.at(4).setPosition(WINDOW_WIDTH - 50, WINDOW_HEIGHT - 50);
}
	

void Menu::setSound(const menuCommand& cmd)
{
	int index{ 4 };
	if (cmd == menuCommand::MUTE)
	{
		m_music.pause();
		index = 5;
	}
	else
		m_music.play();
	m_buttons.at(4).setTexture(&GameResources::getInstance().getMenuTexture(index));

}