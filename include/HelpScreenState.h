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
protected:
	void initilaize()override;
private:
	std::shared_ptr<GameTools> m_gameTools;
};
