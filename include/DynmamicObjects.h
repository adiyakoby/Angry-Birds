#pragma once

#include "Objects.h"


class DynamicObjects : public Objects
{
public:
	DynamicObjects() = default;
	virtual ~DynamicObjects() =  default;

	virtual void drawObject(sf::RenderWindow& window) = 0;
	virtual void objectUpdate() = 0;

protected:
	b2Body* m_body;
private:
	
};


