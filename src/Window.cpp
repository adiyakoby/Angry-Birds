#include "Window.h"

Window::Window() 
	: m_window{sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Angry Birds"}
{
	m_window.setFramerateLimit(60);
	m_window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)));
}


sf::RenderWindow& Window::getWindow() 
{
	return m_window;
}

void Window::setView(float x, float y)
{
	auto view = m_window.getView();
	view.setCenter(x,y);
	m_window.setView(view);
}

