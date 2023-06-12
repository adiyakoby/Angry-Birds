#include "GameController.h"

GameController::GameController()
    :m_menuMode(true)
{
    initBackground();
}

void GameController::runGame()
{

    std::unique_ptr<MyContactListener> contactListener = std::make_unique<MyContactListener>();
    m_world.getWorld()->SetContactListener(contactListener.get());
    //TEMPORARY SECTION TO CHECK BIRD.
    
    createBirds();
    createBuilding();
    createGroundAndRogatka();
    createPigs();
    m_birds[0]->setPosition(sf::Vector2f(m_staticObjects[1]->getPosition().x, m_staticObjects[1]->getPosition().y - 100.f));
     auto view = sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    //view.setViewport(sf::FloatRect(0, 0, 1, 1));
    //view.zoom(0.5);
    m_window.getWindow().setView(view);
    //###############################

    while (m_window.getWindow().isOpen())
    {
        m_window.getWindow().clear();
     
        if (m_menuMode) m_menu.drawMenu(m_window.getWindow());
        else 
        {
            if (m_birds[0].get()->isDragged()) {
                sf::Vector2i mouseLocation = sf::Mouse::getPosition(m_window.getWindow());
                sf::Vector2f worldPosition = m_window.getWindow().mapPixelToCoords(mouseLocation, view); // Convert to world coordinates
                mouseLocation.x = worldPosition.x;
                mouseLocation.y = worldPosition.y;

                m_birds[0].get()->setRangeVector(mouseLocation,m_window.getWindow());
                static_cast<Rogatka*>(m_staticObjects[1].get())->ignoreRogatka();
            }
            drawGame();

        }
        
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
                break;
            }
            }
            auto location = m_window.getWindow().mapPixelToCoords(
                { event.mouseButton.x, event.mouseButton.y });
            for (auto& ea : m_birds)
                ea->handleEvent(event, location);
       
                
        }
        if (!m_menuMode)
        {
            if (m_birds[0]->getPosition().x - view.getSize().x / 2 <= 0)
                view.setCenter(view.getSize() / 2.f);
            else if(m_birds[0]->getPosition().x + view.getSize().x / 2 >= m_background.getSize().x)
                view.setCenter(m_background.getSize().x - view.getSize().x/2, WINDOW_HEIGHT / 2);
            else
                view.setCenter(m_birds[0]->getPosition().x, WINDOW_HEIGHT / 2);

            m_window.getWindow().setView(view);
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
    m_window.getWindow().draw(m_background);
    for (auto& ea : m_building) {
        ea->objectUpdate();
        ea->drawObject(m_window.getWindow());
    }
   for (auto& ea : m_pigs) {
        ea->objectUpdate();
        ea->drawObject(m_window.getWindow());
    }
    m_birds[0]->drawObject(m_window.getWindow());
    m_staticObjects[1]->drawObject(m_window.getWindow());
    //m_staticObjects[0]->drawObject(m_window.getWindow());
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
            m_building.back() = std::move(ObjectFactory<StaticObjects>::instance().create("wood", *m_world.getWorld(), sf::Vector2f(500.f, WINDOW_HEIGHT - 110.f), sf::Vector2f(30.f, 100.f)));
        }
        else if (i == 2)//right
        {
            m_building.emplace_back();
            m_building.back() = std::move(ObjectFactory<StaticObjects>::instance().create("wood", *m_world.getWorld(), sf::Vector2f(700.f, WINDOW_HEIGHT - 110.f), sf::Vector2f(30.f, 100.f)));
            
        }
        else {//top
            m_building.emplace_back();
            m_building.back() = std::move(ObjectFactory<StaticObjects>::instance().create("wood", *m_world.getWorld(), sf::Vector2f(600.f, WINDOW_HEIGHT - 160.f), sf::Vector2f(300.f, 20.f)));

        }
    }
}

void GameController::createGroundAndRogatka()
{
    m_staticObjects[0]= std::make_unique<Ground>(*m_world.getWorld(), sf::Vector2f(0, 0), m_background.getSize());//ground
    m_staticObjects[1] = std::make_unique <Rogatka> (*m_world.getWorld(), sf::Vector2f(300.f,m_staticObjects[0]->getPosition().y - 80.f));//rogatka
}

void GameController::initBackground()
{
    m_background.setTexture(&GameResources::getInstance().getGroundTexture(0));
    m_background.setSize(sf::Vector2f( m_background.getTexture()->getSize().x * 3 , m_background.getTexture()->getSize().y));
    m_background.setPosition(0,0);
}

void GameController::createPigs() {
    m_pigs.emplace_back();
    m_pigs.back() = std::move(ObjectFactory<StaticObjects>::instance().create("Pigs", *m_world.getWorld(), sf::Vector2f(620, WINDOW_HEIGHT - 110.f), sf::Vector2f(20.f, 0.f)));
}
