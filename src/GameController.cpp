#include "GameController.h"

GameController::GameController()
    :m_menuMode(true)
{}

void GameController::runGame()
{
    //TEMPORARY SECTION TO CHECK BIRD.
    
    createBirds();
    createBuilding();
    Ground ground(*m_world.getWorld(), sf::Vector2f(0,0));

   
    
    
    Rogatka rogatka( *m_world.getWorld(), sf::Vector2f(300.f,ground.getPosition().y - 80.f));
    m_birds[0].get()->setPosition(sf::Vector2f(rogatka.getPostion().x, rogatka.getPostion().y - 100.f));
    //###############################

    while (m_window.getWindow().isOpen())
    {
        m_window.getWindow().clear();
        if (m_menuMode) m_menu.drawMenu(m_window.getWindow());
        else {
            drawGame();
           
            ground.drawObject(m_window.getWindow());
            if (m_birds[0].get()->isDragged()) {
                sf::Vector2i mouseLocation = sf::Mouse::getPosition(m_window.getWindow());
                m_birds[0].get()->setRangeVector(mouseLocation,m_window.getWindow());
                rogatka.ignoreRogatka();
            }
            for (auto& ea : m_building) {
                ea->objectUpdate();
                ea->drawObject(m_window.getWindow());
            }
          
            m_birds[0]->drawObject(m_window.getWindow());
            rogatka.drawObject(m_window.getWindow());
            ground.drawObject(m_window.getWindow());

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
                    m_birds[0].get()->handleThrow(location.x, location.y);
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
                    if (m_birds[0].get()->isDragged()) {
                        sf::Vector2f force = m_birds[0].get() -> calculateThrow();
                       m_birds[0].get()-> applyForce(force);
                       
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
    m_world.step(1.f / 60.f, 8, 3);
    
}

void GameController::createBirds()
{
    m_birds.emplace_back();
    m_birds.back() = std::move(ObjectFactory<Bird>::instance().create("Bird", *m_world.getWorld(), sf::Vector2f(0, 0), sf::Vector2f(20.f, 0.f)));
}

void GameController::createBuilding()
{
    for (int i = 0; i < 3; i++)
    {
        //b2World& world, const b2Vec2 bodypostion, const sf::Vector2f position, const sf::Vector2f size
        if (i == 1)//left
        {
            m_building.emplace_back();
            m_building.back() = std::move(ObjectFactory<StaticObjects>::instance().create("wood", *m_world.getWorld(), sf::Vector2f(500.f, 300.f), sf::Vector2f(30.f, 100.f)));
        }
        else if (i == 2)//right
        {
            m_building.emplace_back();
            m_building.back() = std::move(ObjectFactory<StaticObjects>::instance().create("wood", *m_world.getWorld(), sf::Vector2f(700.f, 300.f), sf::Vector2f(30.f, 100.f)));
            
        }
        else {//top
            m_building.emplace_back();
            m_building.back() = std::move(ObjectFactory<StaticObjects>::instance().create("wood", *m_world.getWorld(), sf::Vector2f(600.f, 0.f), sf::Vector2f(300.f, 20.f)));

        }
    }
}


