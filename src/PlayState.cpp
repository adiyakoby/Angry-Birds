#include "PlayState.h"

PlayState::PlayState(std::shared_ptr<GameTools> gameTools)
	:m_gameTools(gameTools), m_contactListener(std::make_unique<MyContactListener>())
{
    m_world.getWorld()->SetContactListener(m_contactListener.get());
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
        static_cast<Rogatka*>(m_staticObjects[1].get())->ignoreRogatka();
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
    m_world.step(1.f / 60.f, 8, 3);
}

void PlayState::drawGame()
{
    m_gameTools->m_window.getWindow().draw(m_background);
    for (auto& ea : m_building) {
        ea->objectUpdate();
        ea->drawObject(m_gameTools->m_window.getWindow());
    }
    for (auto& ea : m_pigs) {
        ea->objectUpdate();
        ea->drawObject(m_gameTools->m_window.getWindow());
    }
    m_birds[0]->drawObject(m_gameTools->m_window.getWindow());
    m_staticObjects[1]->drawObject(m_gameTools->m_window.getWindow());
    //m_staticObjects[0]->drawObject(m_window.getWindow());
   
}

void PlayState::initilaize()
{
    //init background
    m_background.setTexture(&GameResources::getInstance().getGroundTexture(0));
    m_background.setSize(sf::Vector2f(m_background.getTexture()->getSize().x * 3, m_background.getTexture()->getSize().y));
    m_background.setPosition(0, 0);

    //init objects
    createBirds();
    createBuilding();
    createGroundAndRogatka();
    createPigs();

    m_birds[0]->setPosition(sf::Vector2f(m_staticObjects[1]->getPosition().x, m_staticObjects[1]->getPosition().y - 100.f));
}


void PlayState::createBirds()
{
    m_birds.emplace_back();
    m_birds.back() = std::move(ObjectFactory<YellowBird>::instance().create("YellowBird", *m_world.getWorld(), sf::Vector2f(0, 0), sf::Vector2f(20.f, 0.f)));
}

void PlayState::createBuilding()
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

void PlayState::createGroundAndRogatka()
{
    m_staticObjects[0] = std::make_unique<Ground>(*m_world.getWorld(), sf::Vector2f(0, 0), m_background.getSize());//ground
    m_staticObjects[1] = std::make_unique <Rogatka>(*m_world.getWorld(), sf::Vector2f(300.f, m_staticObjects[0]->getPosition().y - 80.f));//rogatka
}

void PlayState::createPigs()
{
    m_pigs.emplace_back();
    m_pigs.back() = std::move(ObjectFactory<StaticObjects>::instance().create("Pigs", *m_world.getWorld(), sf::Vector2f(620, WINDOW_HEIGHT - 110.f), sf::Vector2f(20.f, 0.f)));
}