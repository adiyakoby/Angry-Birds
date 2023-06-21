#include "PlayState.h"

PlayState::PlayState(std::shared_ptr<GameTools> gameTools)
    :m_gameTools(gameTools), m_contactListener(std::make_unique<MyContactListener>()), m_world{ std::make_shared<World>() }, m_lvlsMngr{ m_world }, m_level{1}
{
    m_world->getWorld()->SetContactListener(m_contactListener.get());
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

        m_birds.back()->handleEvent(event, location);
    }

}

void PlayState::update()
{
    if (m_pigs.size() == 0)
    {
        setUpForNextLevel();
        return;
    }
    else if (m_birds.size() == 0)
    {
        setUpForGameOver();
        return;
    }
    deleteObj();
    updateView();
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

void PlayState::setUpForNextLevel()
{
    m_lvlsMngr.getNextLevel(m_birds, m_pigs, m_gameObjects);
    m_level++;
    m_levelData[static_cast<int>(GameData::LEVEL)].second.setString(std::to_string(m_level));
    setNextBird(false);
}

void PlayState::setUpForGameOver()
{
    m_lvlsMngr.getSpecificLevel(m_level, m_birds, m_pigs, m_gameObjects);
    setNextBird(false);
}

void PlayState::Draw()
{
    m_gameTools->m_window.getWindow().clear();
    drawGame();
    m_gameTools->m_window.getWindow().display();
    m_world->step(1.f / 60.f, 8, 3);
}

void PlayState::Resume()
{
    m_lvlsMngr.getNextLevel(m_birds, m_pigs, m_gameObjects);
}

void PlayState::deleteObj()
{
    for (const auto& pig : m_pigs)
    {
        if (pig->getHp() <= 0)
            setScore(pig->getScore());
    }
    std::erase_if(m_pigs, [](const auto& x) {return x->getHp() <= 0; });

    for (const auto& obj : m_gameObjects)
    {
        if (obj->getHp() <= 0)
            setScore(obj->getScore());
    }
    std::erase_if(m_gameObjects, [](const auto& x) {return x->getHp() <= 0; });
}

void PlayState::drawGame()
{
    m_gameTools->m_window.getWindow().draw(m_background);
    for (auto& ea : m_gameObjects) {
        ea->objectUpdate();
        ea->drawObject(m_gameTools->m_window.getWindow());
    }
    for (auto& ea : m_pigs) {
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

void PlayState::updateView()
{

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
}

void PlayState::initilaize()
{ 
    //init background
    m_background.setTexture(&GameResources::getInstance().getTransitionScreens(2));
    m_background.setSize(sf::Vector2f(m_background.getTexture()->getSize().x * 3, m_background.getTexture()->getSize().y));
    m_background.setPosition(0, 0);

    //init Text Data
    createLevelData();

    //init objects
    createGroundAndRogatka();
    m_lvlsMngr.getNextLevel(m_birds, m_pigs , m_gameObjects);
    setNextBird(false);
}

void PlayState::createGroundAndRogatka()
{
    m_worldObjects[0] = std::make_unique<Ground>(m_world, sf::Vector2f(0, 0), m_background.getSize());//ground
    m_worldObjects[1] = std::make_unique <Rogatka>(m_world, sf::Vector2f(ROGATKA_X, ROGATKA_Y));//rogatka
}

void PlayState::createLevelData()
{
    m_levelData.emplace_back().first = GameResources::getInstance().createText("Level: ", sf::Color::White, 1);
    m_levelData.back().second = GameResources::getInstance().createText(std::to_string(m_level), sf::Color::White, 1);
    m_levelData.emplace_back().first = GameResources::getInstance().createText("Score: ", sf::Color::White, 1);
    m_levelData.back().second = GameResources::getInstance().createText("0", sf::Color::White, 1);
    updateDataPosition();
}

void PlayState::updateDataPosition()
{
    float yPos = 50.f;
    for (auto& string : m_levelData)
    {
        string.first.setPosition(sf::Vector2f(m_gameTools->m_window.getWindow().getView().getCenter().x + WINDOW_WIDTH/2 - 155, yPos));
        string.second.setPosition(sf::Vector2f(m_gameTools->m_window.getWindow().getView().getCenter().x+ WINDOW_WIDTH/2 - 65, yPos));
        yPos += 50.f;
    }
}

void PlayState::setScore(int toAdd)
{
    std::string temp = m_levelData[static_cast<int>(GameData::SCORE)].second.getString();
    auto toSet = std::stoi(temp);
    toSet += toAdd;
    m_levelData[static_cast<int>(GameData::SCORE)].second.setString(std::to_string(toSet));

}
