#pragma once

#include "DynmamicObjects.h"


class Wood:public DynamicObjects
{
public:
	Wood(b2World& world, const sf::Vector2f position, const sf::Vector2f size);
	virtual ~Wood() = default;
	
	virtual void objectUpdate();
	virtual void drawObject(sf::RenderWindow& window);
private:
	sf::RectangleShape m_wood;
	void initPhysicBody(b2World& world,const  sf::Vector2f postion, const sf::Vector2f size);
	void initGraphicBody(const sf::Vector2f size);
};
