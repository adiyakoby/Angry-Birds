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
	void setSound(const helpScreenCommand& cmd);
	void drawHelpScreen();

protected:
	void initilaize()override;

private:
	std::shared_ptr<GameTools> m_gameTools;
	std::vector<sf::RectangleShape> m_buttons;
	sf::RectangleShape m_backGround;
	helpScreenCommand m_mode;
	bool m_event;
};
