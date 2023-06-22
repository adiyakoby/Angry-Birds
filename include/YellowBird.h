#pragma once
#include "Bird.h"
class YellowBird : public Bird
{
public:
	YellowBird(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size, arrData arr = {1,BIRD_HP,0});
	virtual ~YellowBird() = default;
    void handleEvent(sf::Event& event, const sf::Vector2f& mouse);

private:
    bool m_secondclick;
};


