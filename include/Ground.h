#pragma once
#include "StaticObjects.h"

class Ground // : public StaicObjects
{
public:
	Ground(b2World& world);
	virtual ~Ground() = default;

	
	virtual void drawObject(sf::RenderWindow& window);
private:
	sf::RectangleShape m_ground;
	b2Body* m_body;

	void initPhysicBody(b2World& world);
	void initGraphicBody();
	
};
