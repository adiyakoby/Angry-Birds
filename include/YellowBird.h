#pragma once
#include "Bird.h"
class YellowBird : public Bird
{
public:
	YellowBird(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size);
	virtual ~YellowBird() = default;
    void handleEvent(sf::Event& event, const sf::Vector2f& mouse);

private:
    bool m_secondclick;
	//void initPhysicBody(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size)override;
	void initGraphicBody(const sf::Vector2f& size = { 15.f, 0.f }) override;
};


