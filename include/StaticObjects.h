#pragma once
#include "Objects.h"



class StaticObjects : public Objects
{
public:
	StaticObjects(std::shared_ptr<World> world, const int& hp = 50) : Objects(world, hp) {};
	virtual ~StaticObjects() = default;

	


private:

};

