#pragma once

#include "StaticObjects.h"

class Pig : public StaticObjects
{

public:
	Pig(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size, arrData arr = {0,0,0});
	virtual ~Pig() = default;

	//virtual funcs
	virtual void objectUpdate()override;
	virtual void drawObject(sf::RenderWindow& window)override;
	virtual inline sf::Vector2f getPosition() const override { return m_pig.getPosition(); }
	virtual void rotate(const int& x) override { ; };
	virtual void hitState() override;

private:
	sf::CircleShape m_pig;

	int m_textuerIndex;
	bool m_hit;

	// Private funcs:
	void initPhysicBody(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size)override;
	void initGraphicBody(const sf::Vector2f& size = { 20.f, 0.f }) override;
};

