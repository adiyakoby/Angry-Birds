#pragma once

#include "GameResources.h"



class Menu
{
public:
	Menu();
	~Menu() = default;

	void drawMenu(sf::RenderWindow& window);
	menuCommand handleClick(const sf::Vector2f &mouse_loc);

private:
	std::vector<sf::Sprite> m_buttons;
	sf::Sprite m_backGround;

	/* init funcs */
	void initButtons();
	

};

