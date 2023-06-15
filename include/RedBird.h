#pragma once
#include "Bird.h"


class RedBird: public Bird
{
public:
	RedBird(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size);
	virtual ~RedBird() = default;

private:
	void initGraphicBody(const sf::Vector2f& size = { 20.f, 0.f });
};


