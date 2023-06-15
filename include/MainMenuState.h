# pragma once


#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>


#include "Macro.h"
#include "State.h"
#include "Game.h"
#include "GameResources.h"
#include "HelpScreenState.h"

class MainMenuState : public State
{
public:
	MainMenuState(std::shared_ptr<GameTools>);
	~MainMenuState() = default;

	void processManeger();
	void update();
	void Draw();

	menuCommand handleClick(const sf::Vector2f& mouse_loc);
	void menuManeger();
	void setSound(const menuCommand& cmd);
	void drawMenu();

protected:
	void initilaize();

private:
	std::shared_ptr<GameTools> m_gameTools;
	std::vector<sf::RectangleShape> m_buttons;
	sf::RectangleShape m_backGround;
	menuCommand m_mode;
	bool m_event;
	sf::Sound m_music;
};
