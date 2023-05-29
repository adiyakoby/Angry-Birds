#include "GameController.h"

GameController::GameController()
{
}

GameController::~GameController()
{
}

void GameController::runGame()
{
    m_window.getWindow()->clear(sf::Color(100, 100, 100, 0));
    //drawGame();
    m_window.getWindow()->display();
    while (m_window.getWindow()->isOpen())
    {
        if (auto event = sf::Event{}; m_window.getWindow()->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.getWindow()->close();
                break;
            case sf::Event::MouseButtonReleased:
            {
                auto location = m_window.getWindow()->mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });
        

                break;
            }
            }
        }
    }

}

void GameController::menuManeger()
{
	
}
