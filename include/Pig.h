#pragma once

#include "StaticObjects.h"

class Pig : public StaticObjects
{

public:
	Pig(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size);
	virtual ~Pig() = default;

	void objectUpdate()override;
	void drawObject(sf::RenderWindow& window)override;
	sf::Vector2f getPosition() const override { return m_pig.getPosition(); }
	void rotate(const int& x) override { ; };

	void hitState();
private:
	sf::CircleShape m_pig;
	void initPhysicBody(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size)override;
	void initGraphicBody(const sf::Vector2f& size = { 20.f, 0.f }) override;
	bool m_hit;
};

