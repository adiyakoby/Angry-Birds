#include "GameController.h"

GameController::GameController()
    :m_menuMode(true)
{}

void GameController::runGame()
{
    m_window.getWindow()->clear(sf::Color(100, 100, 100, 0));
    if (m_menuMode) m_menu.drawMenu();
    else drawGame();
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
                if (m_menuMode)
                {
                    auto mode = m_menu.handleClick(location);

                }
                    
                    

                break;
            }
            }
        }
    }

}

void GameController::menuManeger(const menuCommand& command)
{
    switch (command)
    {
    case menuCommand::PLAY:     m_menuMode = false;             break;
    case menuCommand::HELP:     m_menuMode.setHelp(true);          break;
    case menuCommand::SOUND:    ;                               break;
    case menuCommand::EXIT:     m_window.getWindow()->close();  break;
    }
}

void GameController::drawGame()
{

}


