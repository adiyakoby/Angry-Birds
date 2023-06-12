#pragma once

#include "Macro.h"
#include <iostream>
#include <SFML/Graphics.hpp>




class Window
{
public:
	Window();
	~Window() = default;
	sf::RenderWindow& getWindow();
private:
	sf::RenderWindow m_window;

};

