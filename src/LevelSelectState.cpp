#include "LevelSelectState.h"
#include "PlayState.h"

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
	m_event = false;
}

void LevelSelectState::Draw()
{
	m_gameTools->m_window.getWindow().clear();
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
	//if (m_firstPlay)
	//{
	////	m_gameTools->m_gameStates.addState(std::make_unique<PlayState>(this->m_gameTools, this ->m_sharedData), false);
	//	m_firstPlay = false;
	//}
	//else
		 m_gameTools->m_gameStates.switchStates();
}

void LevelSelectState::updateReturningValue()
{
	if (m_sharedData->levelStatus == "Pass")
		if (m_sharedData->levelToRead < 6)
		{
			if (m_levelData.at(m_sharedData->levelToRead - 1).second < m_sharedData->score)
				m_levelData.at(m_sharedData->levelToRead - 1).second = m_sharedData->score;
			std::cout << "pass level: " << m_sharedData->levelToRead << std::endl;
			std::cout << "level score:  " << m_sharedData->score << std::endl;
			openNewLevel();
		}
			
}

void LevelSelectState::openNewLevel()
{
	m_levelData.emplace_back();
	m_levelData.back().first = "Level " + std::to_string(m_levelData.size());
	//m_levelsFields.at(m_levelData.size() - 1).setTexture();
	std::cout << "open new level " << std::endl;
}

void LevelSelectState::drawLevelSelect()
{
	//m_gameTools->m_window.getWindow().draw(m_backGround);

	for (const auto& i : m_levelsFields)
		m_gameTools->m_window.getWindow().draw(i);

	//m_gameTools->m_window.getWindow().draw(m_backButton);
}

int LevelSelectState::handleClick(sf::Vector2f mouse_loc)
{
	for (int i = 0; i < m_levelsFields.size(); i++)
		if (m_levelsFields.at(i).getGlobalBounds().contains(mouse_loc))
			return i;
	return -1;
}

void LevelSelectState::initilaize()
{
	//m_backGround.setTexture(&GameResources::getInstance().getTransitionScreens(1));
	//m_backGround.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	//m_backGround.setPosition(0, 0);

	//levels fields
	auto firstPos = sf::Vector2f(300.f, 200.f);
	for (int level = 0; level < 2; level++)
	{
		for (int level = 0; level < 3; level++)
		{
			m_levelsFields.emplace_back();
			m_levelsFields.back().setSize(sf::Vector2f(250.f, 250.f));
			m_levelsFields.back().setOrigin(m_levelsFields.back().getSize() * 0.5f);
			m_levelsFields.back().setPosition(firstPos);
			m_levelsFields.back().setFillColor(sf::Color::Yellow);
			m_levelsFields.back().setOutlineColor(sf::Color::White);
			m_levelsFields.back().setOutlineThickness(2);

			firstPos.x += 400.f;
		}
		firstPos = sf::Vector2f(300.f, 500.f);
	}

	//level 1 data
	for(int i = 0; i < 1; i++)
		m_levelData.emplace_back();

	////back button
	//m_levelsFields.emplace_back();
	//m_levelsFields.back().setSize(sf::Vector2f(50.f, 50.f));
	//m_levelsFields.back().setOrigin(m_levelsFields.back().getSize() * 0.5f);
	//m_levelsFields.back().setPosition(sf::Vector2f(100.f, 200.f));
}
