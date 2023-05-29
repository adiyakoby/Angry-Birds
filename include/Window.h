#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>


//Const variables:

const unsigned int WINDOW_WIDTH = 1400;
const unsigned int WINDOW_HEIGHT = 800;

class Window
{
public:
	Window();
	~Window() = default;

	sf::RenderWindow* getWindow();

private:
	sf::RenderWindow m_window;

};

