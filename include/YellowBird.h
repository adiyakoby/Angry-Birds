#pragma once
#include "Bird.h"
class YellowBird : public Bird
{
public:
	YellowBird(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size);
	virtual ~YellowBird() = default;
    void handleEvent(sf::Event& event, const sf::Vector2f& mouse);

private:
    bool m_secondclick;
	void initGraphicBody(const sf::Vector2f& size = { 15.f, 0.f }) override;
};


