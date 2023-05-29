#pragma once

#include "GameResources.h"



class Menu
{
public:
	Menu();
	~Menu() = default;

	void handleClick(const unsigned int& x, const unsigned int& y);

private:
	std::vector<sf::Sprite> m_buttons;
	sf::Sprite m_backGround;

	/* init funcs */
	void initButtons();
	

};

