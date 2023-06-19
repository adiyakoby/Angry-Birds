#include "PlayState.h"

PlayState::PlayState(std::shared_ptr<GameTools> gameTools)
    :m_gameTools(gameTools), m_contactListener(std::make_unique<MyContactListener>()),m_world{std::make_shared<World>()}, m_lvlsMngr{m_world}
{
    m_world->getWorld()->SetContactListener(m_contactListener.get());

    //init Text Data
    createLevelData();
	initilaize();
}

void PlayState::processManeger()
{
    if (m_birds.size() == 0)
        return;
    

    if (m_birds.back()->isDragged()) {
        sf::Vector2i mouseLocation = sf::Mouse::getPosition(m_gameTools->m_window.getWindow());
        sf::Vector2f worldPosition = m_gameTools->m_window.getWindow().mapPixelToCoords(mouseLocation, m_gameTools->m_window.getWindow().getView()); // Convert to world coordinates
        mouseLocation.x = worldPosition.x;
        mouseLocation.y = worldPosition.y;

        m_birds.back().get()->setRangeVector(mouseLocation, m_gameTools->m_window.getWindow());
        static_cast<Rogatka*>(m_worldObjects[1].get())->ignoreRogatka();
    }

    if(m_birds.back()->isOnRogatka() && !m_birds.back()->isDragged())
        static_cast<Rogatka*>(m_worldObjects[1].get())->resetRogatka();


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
        //for (auto& ea : m_birds)
            //ea->handleEvent(event, location);    <- dont need if we only play with one bird at a time, meaning we only send event to the last bird at the vec.
        m_birds.back()->handleEvent(event, location);
    }

}

void PlayState::update()
{
    if (m_birds.size() == 0)
    {
        initilaize();
        return;
    }


    std::erase_if(m_gameObjects, [](const auto& x) {return x->getHp() <= 0; });


    if (m_birds.back()->getPosition().x - m_gameTools->m_window.getWindow().getView().getSize().x / 2 <= 0)
    {
        m_gameTools->m_window.setView(m_gameTools->m_window.getWindow().getView().getSize().x / 2.f, m_gameTools->m_window.getWindow().getView().getSize().y / 2.f);
        updateDataPosition();
    }

    else if (m_birds.back()->getPosition().x + m_gameTools->m_window.getWindow().getView().getSize().x / 2 >= m_background.getSize().x)
    {
        m_gameTools->m_window.setView(m_background.getSize().x - m_gameTools->m_window.getWindow().getView().getSize().x / 2, WINDOW_HEIGHT / 2);
        updateDataPosition();
    }
    else
    {
        m_gameTools->m_window.setView(m_birds.back()->getPosition().x, WINDOW_HEIGHT / 2);
        updateDataPosition();
    }
    if (!(m_birds.back()->isOnRogatka()) && isFinishedMoving())
        setNextBird(true);

    
}

bool PlayState::isFinishedMoving()
{
    if (m_birds.back()->getBodyVelocity().LengthSquared() >= 0.05) 
        return false;
    return std::all_of(m_gameObjects.begin(), m_gameObjects.end(), [](const auto& obj) {return obj->getBodyVelocity().LengthSquared() <= 0.01f; });
}



void PlayState::setNextBird(const bool& x)
{
    if(x) m_birds.pop_back();
    
    if (m_birds.size() > 0)
    {
        static_cast<Rogatka*>(m_worldObjects[1].get())->resetRogatka();
        m_birds.back()->setPosition(std::move(sf::Vector2f(ROGATKA_X, ROGATKA_Y - 50.f)));
        m_birds.back()->setOnRogatka(true);
    }
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

    std::for_each(m_birds.begin(), m_birds.end(), [this](auto& bird) {bird->drawObject(m_gameTools->m_window.getWindow()); });
    
    for (auto& string : m_levelData)
    {
        m_gameTools->m_window.getWindow().draw(string.first);
        m_gameTools->m_window.getWindow().draw(string.second);
    }
       
        
    m_worldObjects[1]->drawObject(m_gameTools->m_window.getWindow());

}

void PlayState::initilaize()
{ 
    //init background
    m_background.setTexture(&GameResources::getInstance().getGroundTexture(0));
    m_background.setSize(sf::Vector2f(m_background.getTexture()->getSize().x * 3, m_background.getTexture()->getSize().y));
    m_background.setPosition(0, 0);

    //init objects
    createGroundAndRogatka();
    m_lvlsMngr.getNextLevel(m_birds, m_gameObjects);
    setNextBird(false);
}

void PlayState::createGroundAndRogatka()
{
    m_worldObjects[0] = std::make_unique<Ground>(m_world, sf::Vector2f(0, 0), m_background.getSize());//ground
    m_worldObjects[1] = std::make_unique <Rogatka>(m_world, sf::Vector2f(ROGATKA_X, ROGATKA_Y));//rogatka
}

void PlayState::createGameObjs()
{
    m_gameObjects = m_lvlsMngr.GetLevel();
}

void PlayState::createLevelData()
{
    m_levelData.emplace_back().first = GameResources::getInstance().createText("Level: ", sf::Color::White, 1);
    m_levelData.back().second = GameResources::getInstance().createText("0", sf::Color::White, 1);
    m_levelData.emplace_back().first = GameResources::getInstance().createText("Score: ", sf::Color::White, 1);
    m_levelData.back().second = GameResources::getInstance().createText("0", sf::Color::White, 1);
    updateDataPosition();
}

void PlayState::updateDataPosition()
{
    float yPos = 50.f;
    for (auto& string : m_levelData)
    {
        string.first.setPosition(sf::Vector2f(m_gameTools->m_window.getWindow().getView().getCenter().x + WINDOW_WIDTH/2 - 150, yPos));
        string.second.setPosition(sf::Vector2f(m_gameTools->m_window.getWindow().getView().getCenter().x+ WINDOW_WIDTH / 2 - 50, yPos));
        yPos += 50.f;
    }
}

void PlayState::setScore()
{
    
}
