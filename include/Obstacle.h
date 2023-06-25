#pragma once

#include "StaticObjects.h"


class Obstacle :public StaticObjects
{
public:
	Obstacle(std::shared_ptr<World> world, const sf::Vector2f &position, const sf::Vector2f& size, arrData arr);
	virtual ~Obstacle() = default;

	void objectUpdate() override;
	void drawObject(sf::RenderWindow& window) override;
	sf::Vector2f getPosition() const override { return m_obstacle.getPosition(); }
	void rotate(const int& x) override { this->rotateBody(); };
	void hitState() override;

private:
	sf::RectangleShape m_obstacle;

	bool m_hit;
	int m_textureIndex;
	int m_halfHp;
	
	// Private funcs:
	void initPhysicBody(std::shared_ptr<World> world, const sf::Vector2f& postion, const sf::Vector2f& size)override;
	void initGraphicBody(const sf::Vector2f& size)override;
};

