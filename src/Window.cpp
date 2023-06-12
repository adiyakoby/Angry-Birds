#include "Window.h"

Window::Window() 
	: m_window{sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Angry Birds"}
{
	m_window.setFramerateLimit(40);
}


sf::RenderWindow& Window::getWindow() 
{
	return m_window;
}

