# pragma once


#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>


#include "Macro.h"
#include "State.h"
#include "Game.h"



class MainMenuState : public State
{
public:
	MainMenuState(std::shared_ptr<GameTools>, bool);
	~MainMenuState() = default;

	void processManeger();
	void update();
	void Draw();
	void Resume()override;
	void Pause()override {}

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
	bool m_newAlloc; //give instraction if we need to allocate new level select state or not
};
