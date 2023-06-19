#pragma once

#include "StaticObjects.h"


class Wood:public StaticObjects
{
public:
	Wood(std::shared_ptr<World> world, const sf::Vector2f position, const sf::Vector2f& size);
	virtual ~Wood() = default;
	
	void objectUpdate() override;
	void drawObject(sf::RenderWindow& window) override;
	sf::Vector2f getPosition() const override { return m_wood.getPosition(); }
	void rotate(const int& x) override {  this->rotateBody(); };

private:
	sf::RectangleShape m_wood;
	void initPhysicBody(std::shared_ptr<World> world,const sf::Vector2f& postion, const sf::Vector2f& size)override;
	void initGraphicBody(const sf::Vector2f& size)override;
};

