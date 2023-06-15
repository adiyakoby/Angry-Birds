#pragma once
#include <box2d/box2d.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>

class Objects;

class LevelManager
{
public:
	LevelManager();
	~LevelManager() = default;
	std::vector<std::shared_ptr<Objects>> GetLevel();
	
private:
	std::ifstream m_lvlsFile;

	/* private funcs */
	std::stack<std::string> ReadLevel();

};

