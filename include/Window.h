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
	void setView(float x, float y);
private:
	sf::RenderWindow m_window;

};

