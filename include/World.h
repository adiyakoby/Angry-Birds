#pragma once
#include <memory>
#include <box2d/box2d.h>
#include "Macro.h"
#include <vector>

enum  Position { Left, Top, Right };
class World
{
public:
	World(/*const b2Vec2 graviry*/);
	~World() = default;

	b2World* getWorld(){ return m_world.get();}
	void step(const float timestep,const int32 velocity,const int32 positionIteration);

private:
	//set the world frame
	std::vector<b2Body*> m_worldFrame;

	std::unique_ptr <b2World> m_world;

	//init functions
	void setFrame();
	b2Body* setCorner(Position position);
};
