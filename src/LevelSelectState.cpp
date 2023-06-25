#include "LevelSelectState.h"
#include "PlayState.h"
#include "MainMenuState.h"

LevelSelectState::LevelSelectState(std::shared_ptr<GameTools> gameTools)
	:m_gameTools{ gameTools }, m_sharedData{ std::make_shared<SharedData>() }, 
	m_event{ false }, m_firstPlay{true}, m_requestedLevel{0}
{
	initilaize();
}

void LevelSelectState::processManeger()
{
	if (m_firstPlay)
	{
		m_gameTools->m_gameStates.addState(std::make_unique<PlayState>(this->m_gameTools, this->m_sharedData), false);
		m_gameTools->m_gameStates.switchStates();
		m_firstPlay = false;
	}
	if (auto event = sf::Event{}; m_gameTools->m_window.getWindow().pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_gameTools->m_window.getWindow().close();
			break;


		case sf::Event::MouseButtonReleased:
		{
			auto location = m_gameTools->m_window.getWindow().mapPixelToCoords(
				{ event.mouseButton.x, event.mouseButton.y });

			m_requestedLevel = handleClick(location);
			m_event = true;
			break;
		}
		}
	}

}

void LevelSelectState::update()
{
	if (m_event)
		if (m_requestedLevel >= 0 && m_requestedLevel < m_levelData.size())
			levelRequest();
		else if (m_requestedLevel == 7)
			m_gameTools->m_gameStates.addState(std::make_unique<MainMenuState>(this->m_gameTools, false), false);
	m_event = false;
}

void LevelSelectState::Draw()
{
	m_gameTools->m_window.getWindow().clear(sf::Color::Green);
	drawLevelSelect();
	m_gameTools->m_window.getWindow().display();
}

void LevelSelectState::Resume()
{
	updateReturningValue();
}

void LevelSelectState::levelRequest()
{
	std::cout << "requested level " << m_requestedLevel + 1 << std::endl;
	m_sharedData->levelToRead = m_requestedLevel + 1;
	m_gameTools->m_gameStates.switchStates();
}

void LevelSelectState::updateReturningValue()
{
	if (m_sharedData->levelStatus == "Pass" )	
	{
		if (m_levelData.at(m_sharedData->levelToRead - 1).second < m_sharedData->score)
		{
			m_levelData.at(m_sharedData->levelToRead - 1).second = m_sharedData->score;
			m_levelsFields.at(m_sharedData->levelToRead - 1).second.setString(m_levelData.at(m_sharedData->levelToRead - 1).first + std::to_string(m_levelData.at(m_sharedData->levelToRead - 1).second));
		}
		std::cout << "pass level: " << m_sharedData->levelToRead << std::endl;
		std::cout << "level score:  " << m_sharedData->score << std::endl;
		if (m_sharedData->levelToRead == m_levelData.size())
			openNewLevel();
	}
			
}

void LevelSelectState::openNewLevel()
{
	m_levelData.emplace_back();
	m_levelData.back().first = "Score: ";
	m_levelData.back().second = 0;
	int newLevel = m_levelData.size() - 1;
	m_levelsFields.at(newLevel).first.setTexture(&GameResources::getInstance().getLevelsFields(newLevel), true);
	m_levelsFields.at(newLevel).second = GameResources::getInstance().createText(m_levelData.at(newLevel).first + std::to_string(m_levelData.at(newLevel).second), sf::Color::White, 0);
	m_levelsFields.at(newLevel).second.setPosition(m_levelsFields.at(newLevel).first.getPosition() + sf::Vector2f(0, 50));
	m_levelsFields.at(newLevel).second.setCharacterSize(25);
	std::cout << "open new level " << std::endl;
}

void LevelSelectState::drawLevelSelect()
{
	m_gameTools->m_window.getWindow().draw(m_backGround);

	for (const auto& i : m_levelsFields)
	{
		m_gameTools->m_window.getWindow().draw(i.first);
		m_gameTools->m_window.getWindow().draw(i.second);
	}
		
	m_gameTools->m_window.getWindow().draw(m_backButton);
}

int LevelSelectState::handleClick(sf::Vector2f mouse_loc)
{
	for (int i = 0; i < m_levelsFields.size(); i++)
		if (m_levelsFields.at(i).first.getGlobalBounds().contains(mouse_loc))
			return i;
	if (m_backButton.getGlobalBounds().contains(mouse_loc))
		return 7;
	return -1;
}

void LevelSelectState::initilaize()
{
	
	m_backGround.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	m_backGround.setPosition(0, 0);
	m_backGround.setTexture(&GameResources::getInstance().getBackGroundScreens(3));
	
	//levels fields
	auto firstPos = sf::Vector2f(300.f, 200.f);
	for (int level = 0; level < 2; level++)
	{
		for (int level = 0; level < 3; level++)
		{
			m_levelsFields.emplace_back();
			m_levelsFields.back().first.setSize(sf::Vector2f(200.f, 200.f));
			m_levelsFields.back().first.setOrigin(m_levelsFields.back().first.getSize() * 0.5f);
			m_levelsFields.back().first.setPosition(firstPos);
			m_levelsFields.back().first.setTexture(&GameResources::getInstance().getLock());
			firstPos.x += 400.f;
		}
		firstPos = sf::Vector2f(300.f, 500.f);
	}

	//give access to level 1

	m_levelData.emplace_back();
	m_levelData.back().first = "Score: ";
	m_levelData.back().second = 0;
	m_levelsFields.at(0).first.setTexture(&GameResources::getInstance().getLevelsFields(0), true);
	m_levelsFields.at(0).second = GameResources::getInstance().createText(m_levelData.at(0).first + std::to_string(m_levelData.at(0).second), sf::Color::White, 0);
	m_levelsFields.at(0).second.setPosition(sf::Vector2f(300, 250));
	m_levelsFields.at(0).second.setCharacterSize(25);

	////back button
	m_backButton.setRadius(50.f);
	m_backButton.setOrigin(m_backButton.getRadius(),m_backButton.getRadius());
	m_backButton.setPosition(sf::Vector2f(100.f, WINDOW_HEIGHT - 100));
	m_backButton.setTexture(&GameResources::getInstance().getButtons(0));
	
}
