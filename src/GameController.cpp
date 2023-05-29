#include "GameController.h"

GameController::GameController()
    :m_menuMode(true)
{}

void GameController::runGame()
{

    while (m_window.getWindow().isOpen())
    {
        m_window.getWindow().clear(sf::Color::Red);
        if (m_menuMode) m_menu.drawMenu(m_window.getWindow());
        else drawGame();
        m_window.getWindow().display();
        if (auto event = sf::Event{}; m_window.getWindow().pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.getWindow().close();
                break;
            case sf::Event::MouseButtonReleased:
            {
                auto location = m_window.getWindow().mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });
                if (m_menuMode)
                {
                    auto mode = m_menu.handleClick(location);
                    menuManeger(mode);
                }
                else
                {
                    ;
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
    case menuCommand::HELP:     m_menu.setHelp(true);           break;
    case menuCommand::BACK:     m_menu.setHelp(false);          break;
    case menuCommand::MUTE:    ;
    case menuCommand::SOUND:    m_menu.setSound(command);       break;
    case menuCommand::EXIT:     m_window.getWindow().close();   break;
    default:                                                    break;
    }
}

void GameController::drawGame()
{
    ;
}


