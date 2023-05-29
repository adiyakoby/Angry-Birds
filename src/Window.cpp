#include "Window.h"

Window::Window() : m_window{sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Angry Birds"}
{

};


sf::RenderWindow* Window::getWindow()
{
	return &m_window;
};

void Window::setWindow()
{

};