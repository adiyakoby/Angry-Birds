#pragma once

#include "State.h"
#include "Game.h"

class TransitionScreens : public State
{
public:
	TransitionScreens(std::shared_ptr<GameTools>, const int&);
	~TransitionScreens() = default;
	void processManeger()override;
	void update()override;
	void Draw()override;
	void Resume()override {}
	void Pause()override {}
protected:
	void initilaize();
private:
	sf::Clock m_stateClock;
	float m_stateTimeLimit;
	std::shared_ptr<GameTools> m_gameTools;
	sf::RectangleShape m_TransitionScreen;
	int m_texture;
};

