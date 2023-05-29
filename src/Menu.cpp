#include "Menu.h"

Menu::Menu()
	:m_helpScreen(false)
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
	for (size_t i = 0; i < 3; i++)
		if (m_buttons.at(i).getGlobalBounds().contains(mouse_loc))
			return static_cast<menuCommand>(i);
}

void Menu::initButtons()
{ 
	m_backGround.setTexture(&GameResources::getInstance().getMenuTexture(0));
	m_backGround.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	m_backGround.setPosition(0, 0);
	
}
	