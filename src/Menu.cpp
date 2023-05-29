#include "Menu.h"

Menu::Menu()
{
	initButtons();
};

void Menu::drawMenu(sf::RenderWindow& window)
{
	if (m_helpScreen); // PRINT HELP
	else {
		window.draw(m_backGround);
		for (auto& ea : m_buttons)
			window.draw(ea);
	}
	
}
void Menu::setHelp(const bool& x)
{
	m_helpScreen = x;
}
menuCommand Menu::handleClick(const sf::Vector2f& mouse_loc)
{ 
	for (size_t i = 0; i < m_buttons.size() ; i++)
		if (m_buttons.at(i).getGlobalBounds().contains(mouse_loc))
			return static_cast<menuCommand>(i);
}

void Menu::initButtons()
{ 
	m_backGround.setTexture(&GameResources::getInstance().getTransitionScreens(0));
	// "play.png", "help.png", "back.png", "exit.png", "sound.png", "mute.png"
	for (size_t i = 0; i < 6; i++)
	{
		m_buttons.emplace_back();
		m_buttons.back().setTexture(&GameResources::getInstance().getMenuTexture(i));
		m_buttons.back().setOrigin(m_buttons.back().getGlobalBounds().width / 2, m_buttons.back().getGlobalBounds().height / 2);
		
	}
}
	