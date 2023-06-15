#pragma once


#include "StaticObjects.h"
#include "RedBird.h"
#include "YellowBird.h"
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

	void getNextLevel(std::vector<std::unique_ptr<Bird>>& birdsVec, std::vector<std::unique_ptr<StaticObjects>> &objVec);
	
private:
	std::ifstream m_lvlsFile;
	std::shared_ptr<World> m_world;

	/* private funcs */
	std::deque<std::string> ReadBirds();
	std::deque<std::string> ReadLevel();
	std::vector<std::unique_ptr<StaticObjects>> CreateObj(std::deque<std::string> &objDeq);
	std::vector<std::unique_ptr<Bird>> CreateBirds(std::deque<std::string>& objDeq);

	

};

