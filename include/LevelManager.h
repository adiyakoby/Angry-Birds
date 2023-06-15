#pragma once


#include "StaticObjects.h"
#include "World.h"

#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>

class Objects;

class LevelManager
{
public:
	LevelManager(std::shared_ptr<World> world);
	~LevelManager() = default;

	std::vector<std::unique_ptr<StaticObjects>> GetLevel();
	
private:
	std::ifstream m_lvlsFile;
	std::shared_ptr<World> m_world;

	/* private funcs */
	std::deque<std::string> ReadLevel();
	std::vector<std::unique_ptr<StaticObjects>> CreateObj(std::deque<std::string> &objDeq);
	

};

