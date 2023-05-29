#include "Menu.h"

Menu::Menu()
{
	initButtons();
};

void Menu::handleClick(const unsigned int& x, const unsigned int& y)
{ }

void Menu::initButtons()
{ 
	m_backGround.setTexture(GameResources::getInstance().getMenuTexture(0));
}
	