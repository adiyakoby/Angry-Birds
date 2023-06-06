#pragma once
#include "StaticObjects.h"

class Ground : public StaticObjects
{
public:
	Ground(b2World& world);
	 ~Ground() = default;

	
	virtual void drawObject(sf::RenderWindow& window);
private:
	sf::RectangleShape m_ground;

	//init functions
	void initPhysicBody(b2World& world);
	void initGraphicBody();
	
};
