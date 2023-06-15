#include "PlayState.h"

PlayState::PlayState(std::shared_ptr<GameTools> gameTools)
    :m_gameTools(gameTools), m_contactListener(std::make_unique<MyContactListener>()),m_world{std::make_shared<World>()}, m_lvlsMngr{m_world}
{
    m_world->getWorld()->SetContactListener(m_contactListener.get());
	initilaize();
}

void PlayState::processManeger()
{
    if (m_birds[0].get()->isDragged()) {
        sf::Vector2i mouseLocation = sf::Mouse::getPosition(m_gameTools->m_window.getWindow());
        sf::Vector2f worldPosition = m_gameTools->m_window.getWindow().mapPixelToCoords(mouseLocation, m_gameTools->m_window.getWindow().getView()); // Convert to world coordinates
        mouseLocation.x = worldPosition.x;
        mouseLocation.y = worldPosition.y;

        m_birds[0].get()->setRangeVector(mouseLocation, m_gameTools->m_window.getWindow());
        static_cast<Rogatka*>(m_worldObjects[1].get())->ignoreRogatka();
    }

    if (auto event = sf::Event{}; m_gameTools->m_window.getWindow().pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_gameTools->m_window.getWindow().close();
            break;
        }
        auto location = m_gameTools->m_window.getWindow().mapPixelToCoords(
            { event.mouseButton.x, event.mouseButton.y }, m_gameTools->m_window.getWindow().getView());
        for (auto& ea : m_birds)
            ea->handleEvent(event, location);
    }

}

void PlayState::update()
{
    if (m_birds[0]->getPosition().x - m_gameTools->m_window.getWindow().getView().getSize().x / 2 <= 0)
        m_gameTools->m_window.setView(m_gameTools->m_window.getWindow().getView().getSize().x / 2.f, m_gameTools->m_window.getWindow().getView().getSize().y / 2.f);
    else if (m_birds[0]->getPosition().x + m_gameTools->m_window.getWindow().getView().getSize().x / 2 >= m_background.getSize().x)
        m_gameTools->m_window.setView(m_background.getSize().x - m_gameTools->m_window.getWindow().getView().getSize().x / 2, WINDOW_HEIGHT / 2);
    else
        m_gameTools->m_window.setView(m_birds[0]->getPosition().x, WINDOW_HEIGHT / 2);
}

void PlayState::Draw()
{
    m_gameTools->m_window.getWindow().clear();
    drawGame();
    m_gameTools->m_window.getWindow().display();
    m_world->step(1.f / 60.f, 8, 3);
}

void PlayState::drawGame()
{
    m_gameTools->m_window.getWindow().draw(m_background);
    for (auto& ea : m_gameObjects) {
        ea->objectUpdate();
        ea->drawObject(m_gameTools->m_window.getWindow());
    }
    m_birds[0]->drawObject(m_gameTools->m_window.getWindow());
    m_worldObjects[1]->drawObject(m_gameTools->m_window.getWindow());
    //m_staticObjects[0]->drawObject(m_window.getWindow());
   
}

void PlayState::initilaize()
{
    //init background
    m_background.setTexture(&GameResources::getInstance().getGroundTexture(0));
    m_background.setSize(sf::Vector2f(m_background.getTexture()->getSize().x * 3, m_background.getTexture()->getSize().y));
    m_background.setPosition(0, 0);

    //init objects
    // 
    //createBirds();      -> Dont need becasue of lvl manager
    //createGameObjs(); -> Dont need becasue of lvl manager

    createGroundAndRogatka();
    m_lvlsMngr.getNextLevel(m_birds, m_gameObjects);

    m_birds[0]->setPosition(sf::Vector2f(m_worldObjects[1]->getPosition().x, m_worldObjects[1]->getPosition().y - 100.f));
}


void PlayState::createBirds()
{
    m_birds.emplace_back(std::move(ObjectFactory<RedBird>::instance().create("RedBird", *m_world->getWorld(), sf::Vector2f(0, 0), sf::Vector2f(20.f, 0.f))));
}


void PlayState::createGroundAndRogatka()
{
    m_worldObjects[0] = std::make_unique<Ground>(*m_world->getWorld(), sf::Vector2f(0, 0), m_background.getSize());//ground
    m_worldObjects[1] = std::make_unique <Rogatka>(*m_world->getWorld(), sf::Vector2f(300.f, m_worldObjects[0]->getPosition().y - 80.f));//rogatka
}

void PlayState::createGameObjs()
{
    m_gameObjects = m_lvlsMngr.GetLevel();
}