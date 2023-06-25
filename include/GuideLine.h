#pragma once

#include <vector>

#include "World.h"

class GuideLine
{
public:
	
	static GuideLine& getInstance();
	GuideLine(const GuideLine&) = delete; //disable copy constructor
	GuideLine operator=(const GuideLine&) = delete; //disable assimenget operator

	void setWorld(std::shared_ptr<World> world);
	void drawGuideLine(sf::RenderWindow& window);
	void reset() { m_bodies.clear(); m_guideline.clear(); }
	void setPosition(const sf::Vector2f& pos);

private:
	//private constructor and destructor
	GuideLine();
	~GuideLine() = default;

	//private memebrs
	std::vector<b2Body*> m_bodies;
	std::vector<sf::CircleShape> m_guideline;
	std::shared_ptr<World> m_world;

	//private funcs
	void initPhysicBody();
	void initGraphicBody();

};

