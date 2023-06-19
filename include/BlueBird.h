#pragma once

#include "Bird.h"


class BlueBird : public Bird
{
public:
	BlueBird(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size);
	virtual ~BlueBird() = default;

private:

};
