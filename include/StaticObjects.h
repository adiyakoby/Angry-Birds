#pragma once
#include "Objects.h"



class StaticObjects : public Objects
{
public:
	StaticObjects() = default;
	virtual ~StaticObjects() = default;

	virtual void drawObject(sf::RenderWindow& window) = 0;
protected:
	b2Body* m_body;

private:
	
};

