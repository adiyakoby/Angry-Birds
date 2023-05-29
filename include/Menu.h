#pragma once

#include "GameResources.h"



class Menu
{
public:
	Menu();
	~Menu() = default;

	void setHelp(const bool &x);
	void drawMenu(sf::RenderWindow& window);
	menuCommand handleClick(const sf::Vector2f &mouse_loc);

private:
	std::vector<sf::RectangleShape> m_buttons;
	sf::RectangleShape m_backGround;
	menuCommand m_menu_state;

	bool m_helpScreen;

	/* init funcs */
	void initButtons();
	

};

