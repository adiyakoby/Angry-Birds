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


static auto registerItRedBird = ObjectFactory<RedBird>::instance().registerType(
    "RedBird",
    [](b2World& world, const sf::Vector2f& position, const sf::Vector2f& size) -> std::unique_ptr<RedBird>
    {
        return std::make_unique<RedBird>(world, position, size);
    }
);
