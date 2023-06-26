#pragma once

#include "State.h"
#include "Game.h"

class HelpScreenState : public State
{
public:
	HelpScreenState(std::shared_ptr<GameTools> gameTools);
	virtual ~HelpScreenState() = default;

	void processManeger()override;
	void update()override;
	void Draw()override;
	void Resume()override {}
	void Pause()override {}

	helpScreenCommand handleClick(const sf::Vector2f& mouse_loc);
	void helpManeger();
	void drawHelpScreen();
	void moveBetweenPages();
protected:
	void initilaize()override;

private:
	std::shared_ptr<GameTools> m_gameTools;
	sf::RectangleShape m_backButton;
	std::vector<sf::CircleShape> m_Buttons;
	sf::RectangleShape m_backGround;
	int m_currentInstructionPage;
	helpScreenCommand m_direction;
	helpScreenCommand m_mode;
	bool m_event;
};
