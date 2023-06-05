#include "GameController.h"

GameController::GameController()
    :m_menuMode(true){

    initWorld();
}

void GameController::initWorld() {
    
    b2Vec2 gravity(0.f, 10.8f);
    m_world = std::make_unique<b2World>(gravity);
    m_world->SetGravity(gravity);
}
void GameController::runGame()
{
    
    //TEMPORARY SECTION TO CHECK BIRD.
    
    Bird bird(*m_world.get());
    Ground ground(*m_world.get());
    //###############################
    m_window.getWindow().setFramerateLimit(60);

    while (m_window.getWindow().isOpen())
    {
        m_window.getWindow().clear();
        if (m_menuMode) m_menu.drawMenu(m_window.getWindow());
        else {
            drawGame();
            bird.drawObject(m_window.getWindow());
            ground.drawObject(m_window.getWindow());
            if (bird.isDragged()) {
                sf::Vector2i mouseLocation = sf::Mouse::getPosition(m_window.getWindow());
                bird.setRangeVector(mouseLocation);
            }

        }
        m_window.getWindow().display();
        if (auto event = sf::Event{}; m_window.getWindow().pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.getWindow().close();
                break;
    
            case sf::Event::MouseButtonPressed:
            {
                auto location = m_window.getWindow().mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    bird.handleThrow(location.x, location.y);
                }
                break;
            }
            //in this case when mouse is not move the bird falls down maybe later.
             /* case sf::Event::MouseMoved:
            {
                sf::Vector2i mouseLocation = sf::Mouse::getPosition(m_window.getWindow());
                if (bird.isDragged())
                    bird.setRangeVector(mouseLocation);
                break;
            }*/
            case sf::Event::MouseButtonReleased:
            {
                auto location = m_window.getWindow().mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });
                if (m_menuMode)
                {
                    auto mode = m_menu.handleClick(location);
                    menuManeger(mode);
                }
                else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                {
                    if (bird.isDragged()) {
                        sf::Vector2f force = bird.calculateThrow();
                        bird.applyForce(force);
                    }
                    break;
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
    m_world->Step(1.f / 60.f, 8, 3);
    ;
}


