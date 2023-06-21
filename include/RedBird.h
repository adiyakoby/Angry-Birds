#pragma once
#include "Bird.h"


class RedBird: public Bird
{
public:
	RedBird(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size);
	virtual ~RedBird() = default;

private:
};


