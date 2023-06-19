#pragma once

#include "Bird.h"

enum BirdState {
	normal,
	split
};


class BlueBird : public Bird
{
public:
	BlueBird(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size);
	virtual ~BlueBird() = default;

	void handleEvent(sf::Event& event, const sf::Vector2f& mouse);
	void objectUpdate();
	void drawObject(sf::RenderWindow& w);
private:
	std::array<std::unique_ptr<BlueBird>,3> m_split;
	void initGraphicBody(const sf::Vector2f& size = { 15.f, 0.f }) override;
	std::shared_ptr<World> m_world;
	bool isSplit;
	BirdState m_state;
};
