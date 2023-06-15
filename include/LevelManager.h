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
	std::vector<std::shared_ptr<Objects>> GetLevel();
	
private:
	std::ifstream m_lvlsFile;

	/* private funcs */
	std::deque<std::string> ReadLevel();
	std::shared_ptr<Objects> CreateObj(const char &x);
	std::shared_ptr<World> m_world;

};

