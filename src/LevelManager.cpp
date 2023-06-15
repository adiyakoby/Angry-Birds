#include "LevelManager.h"

LevelManager::LevelManager() : m_lvlsFile() {
	m_lvlsFile.open("GameLevels.txt", std::ifstream::in);
}

std::vector<std::shared_ptr<Objects>> LevelManager::GetLevel()
{
	std::cout << " GetLevel() \n";

	std::stack<std::string> objStack{ ReadLevel()};
	std::cout << "objStack side in GETLEVEL is : " << objStack.size() << std::endl;

	while (!objStack.empty())
	{
		std::string temp = objStack.top();
		std::cout << temp << std::endl;
		objStack.pop();
	}

	return std::vector<std::shared_ptr<Objects>>();
}


std::stack<std::string> LevelManager::ReadLevel()
{
	std::cout << "ReadLevel()" << std::endl;

	std::stack<std::string> objStack;
	std::string temp;
	while (m_lvlsFile.is_open() && m_lvlsFile.good())
	{
		std::getline(m_lvlsFile, temp);
		std::cout << "now read line " << temp << std::endl;
		objStack.push(temp);
	}
	return objStack;
}