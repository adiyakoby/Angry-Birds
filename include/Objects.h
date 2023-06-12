#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Macro.h"
#include "GameResources.h"
#include "ObjectFactory.h"

class Objects
{
public:
	Objects() : m_hp{ 100 } {}
	virtual ~Objects() = default;

	virtual void objectUpdate() = 0;
	virtual void drawObject(sf::RenderWindow& window) = 0;

	int getHp() const { return m_hp; }
	void setHp(int damage) { m_hp -= damage; }

protected:
	b2Body* m_body;
	virtual void initPhysicBody(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size) = 0;
	virtual void initGraphicBody(const sf::Vector2f size) = 0;

private:
	int m_hp;

};

