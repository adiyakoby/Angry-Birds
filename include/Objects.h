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
	virtual sf::Vector2f getPosition() const = 0;
	int getHp() const { return m_hp; }
	void setDamage(int damage) { m_hp -= damage; }
	void setHp(int hp) { m_hp = hp; };
	virtual void rotate(const int& x) = 0;
	void rotateBody() { m_body->SetTransform(m_body->GetPosition(), m_body->GetAngle() + b2_pi / 2.0f); };
	const b2Vec2& getBodyVelocity() { return m_body->GetLinearVelocity(); };

protected:
	b2Body* m_body;
	virtual void initPhysicBody(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size) = 0;
	virtual void initGraphicBody(const sf::Vector2f& size) = 0;

private:
	int m_hp;

};

