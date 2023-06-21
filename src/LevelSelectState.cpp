#include "LevelSelectState.h"

LevelSelectState::LevelSelectState(std::shared_ptr<GameTools> gameTools)
	:m_gameTools{ gameTools }, m_sharedData{ std::make_shared<SharedData>() }, m_event{false}
{
	initilaize();
}

void LevelSelectState::processManeger()
{
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

			//m_mode = handleClick(location);
			m_event = true;
			break;
		}
		}
	}

}

void LevelSelectState::update()
{
	;
}

void LevelSelectState::Draw()
{
	m_gameTools->m_window.getWindow().clear();
	drawLevelSelect();
	m_gameTools->m_window.getWindow().display();
}

void LevelSelectState::drawLevelSelect()
{
	//m_gameTools->m_window.getWindow().draw(m_backGround);

	for (const auto& i : m_levelsFields)
		m_gameTools->m_window.getWindow().draw(i);

	m_gameTools->m_window.getWindow().draw(m_backButton);
}

void LevelSelectState::initilaize()
{
	//m_backGround.setTexture(&GameResources::getInstance().getTransitionScreens(1));
	//m_backGround.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	//m_backGround.setPosition(0, 0);

	//levels fields
	auto firstPos = sf::Vector2f(150.f, 300);
	for (int level = 0; level < 6; level++)
	{
		m_levelsFields.emplace_back();
		m_levelsFields.back().setSize(sf::Vector2f(100.f, 200.f));
		m_levelsFields.back().setOrigin(m_levelsFields.back().getSize() * 0.5f);
		m_levelsFields.back().setPosition(sf::Vector2f(100.f, 200.f));
		m_levelsFields.back().setFillColor(sf::Color::Yellow);
		m_levelsFields.back().setOutlineColor(sf::Color::White);
		m_levelsFields.back().setOutlineThickness(2);
		
		firstPos += sf::Vector2f(150.f, 300.f);
	}

	//back button
	m_levelsFields.emplace_back();
	m_levelsFields.back().setSize(sf::Vector2f(50.f, 50.f));
	m_levelsFields.back().setOrigin(m_levelsFields.back().getSize() * 0.5f);
	m_levelsFields.back().setPosition(sf::Vector2f(100.f, 200.f));
}
