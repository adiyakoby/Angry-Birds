#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Macro.h"
#include "GameResources.h"
#include "ObjectFactory.h"

class Objects
{
public:
	Objects() = default;
	virtual ~Objects() = default;

	virtual void drawObject(sf::RenderWindow& window) = 0;

private:

};

