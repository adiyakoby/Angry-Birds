#include "PlayState.h"

PlayState::PlayState(std::shared_ptr<GameTools> gameTools)
    :m_gameTools(gameTools), m_contactListener(std::make_unique<MyContactListener>()),m_world{std::make_shared<World>()}, m_lvlsMngr{m_world}
{
    m_world->getWorld()->SetContactListener(m_contactListener.get());

	initilaize();
}

void PlayState::processManeger()
{
    if (m_birds.size() == 0)
        return;
    

    if (m_birds.back().get()->isDragged()) {
        sf::Vector2i mouseLocation = sf::Mouse::getPosition(m_gameTools->m_window.getWindow());
        sf::Vector2f worldPosition = m_gameTools->m_window.getWindow().mapPixelToCoords(mouseLocation, m_gameTools->m_window.getWindow().getView()); // Convert to world coordinates
        mouseLocation.x = worldPosition.x;
        mouseLocation.y = worldPosition.y;

        m_birds.back().get()->setRangeVector(mouseLocation, m_gameTools->m_window.getWindow());
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
        //for (auto& ea : m_birds)
            //ea->handleEvent(event, location);    <- dont need if we only play with one bird at a time, meaning we only send event to the last bird at the vec.
        m_birds.back()->handleEvent(event, location);
    }

}

void PlayState::update()
{
    if (m_birds.size() == 0)
    {
        m_world->getWorld()->SetContactListener(nullptr);
        m_world = std::make_shared<World>();
        initilaize();
        m_world->getWorld()->SetContactListener(m_contactListener.get());
        return;
    }

    
    std::erase_if(m_gameObjects, [](const auto& x) {return x->getHp() <= 0; });
 

    if (m_birds.back()->getPosition().x - m_gameTools->m_window.getWindow().getView().getSize().x / 2 <= 0)
        m_gameTools->m_window.setView(m_gameTools->m_window.getWindow().getView().getSize().x / 2.f, m_gameTools->m_window.getWindow().getView().getSize().y / 2.f);
    else if (m_birds.back()->getPosition().x + m_gameTools->m_window.getWindow().getView().getSize().x / 2 >= m_background.getSize().x)
        m_gameTools->m_window.setView(m_background.getSize().x - m_gameTools->m_window.getWindow().getView().getSize().x / 2, WINDOW_HEIGHT / 2);
    else
        m_gameTools->m_window.setView(m_birds.back()->getPosition().x, WINDOW_HEIGHT / 2);

    if (!m_birds.back()->isOnRogatka() && m_birds.back()->getBodyVelocity().LengthSquared() == 0) setNextBird();
    
}

void PlayState::setNextBird()
{
    m_birds.pop_back();
    if (m_birds.size() > 0)
    {
        m_birds.back()->setPosition(std::move(sf::Vector2f(m_worldObjects[1]->getPosition().x, m_worldObjects[1]->getPosition().y - 100.f)));
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


    //m_birds[0]->drawObject(m_gameTools->m_window.getWindow());
    //m_staticObjects[0]->drawObject(m_window.getWindow());
   
}

void PlayState::initilaize()
{
   
    std::cout << " in  initilaize()" << std::endl;
    //init background
    m_background.setTexture(&GameResources::getInstance().getGroundTexture(0));
    m_background.setSize(sf::Vector2f(m_background.getTexture()->getSize().x * 3, m_background.getTexture()->getSize().y));
    m_background.setPosition(0, 0);

    //init objects
    // 
    //createBirds();      -> Dont need becasue of lvl manager
    //createGameObjs(); -> Dont need becasue of lvl manager
    std::cout << " got here \n";
    createGroundAndRogatka();
    m_lvlsMngr.getNextLevel(m_birds, m_gameObjects);
    birdsPosition(); 
    std::cout << "finished making new lvl" << std::endl;
    //m_birds[0]->setPosition(sf::Vector2f(m_worldObjects[1]->getPosition().x, m_worldObjects[1]->getPosition().y - 100.f));
    createLevelData();
}

void PlayState::birdsPosition()
{
    sf::Vector2f rogatkaPos{ m_worldObjects[1]->getPosition().x, m_worldObjects[1]->getPosition().y - 100.f };

    for (size_t i = 0; i < m_birds.size() ; i++)
    {
        if (i == m_birds.size()-1)
        {
            m_birds[i]->setPosition(std::move(sf::Vector2f(m_worldObjects[1]->getPosition().x, m_worldObjects[1]->getPosition().y - 100.f)));
            m_birds[i]->setOnRogatka(true);
        }
            
        else
        {
            m_birds[i]->setPosition(std::move(sf::Vector2f(rogatkaPos.x - 100.f, rogatkaPos.y - 100.f)));
            rogatkaPos.x -= 100;

        }

    }
}

void PlayState::createBirds()
{
    m_birds.emplace_back(std::move(ObjectFactory<RedBird>::instance().create("RedBird", m_world, sf::Vector2f(0, 0), sf::Vector2f(20.f, 0.f))));
}


void PlayState::createGroundAndRogatka()
{
    m_worldObjects[0] = std::make_unique<Ground>(m_world, sf::Vector2f(0, 0), m_background.getSize());//ground
    m_worldObjects[1] = std::make_unique <Rogatka>(m_world, sf::Vector2f(300.f, m_worldObjects[0]->getPosition().y - 80.f));//rogatka
}

void PlayState::createGameObjs()
{
    m_gameObjects = m_lvlsMngr.GetLevel();
}

void PlayState::createLevelData()
{
    m_levelData.emplace_back().first = GameResources::getInstance().createText("Level: ", sf::Vector2f(WINDOW_WIDTH - 150, 50), sf::Color::White, 1);
    m_levelData.back().second = GameResources::getInstance().createText("0", sf::Vector2f(WINDOW_WIDTH - 50, 50), sf::Color::White, 1);
    m_levelData.emplace_back().first = GameResources::getInstance().createText("Score: ", sf::Vector2f(WINDOW_WIDTH - 150, 100), sf::Color::White, 1);
    m_levelData.back().second = GameResources::getInstance().createText("0", sf::Vector2f(WINDOW_WIDTH - 50, 100), sf::Color::White, 1);
}
