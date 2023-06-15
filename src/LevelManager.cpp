#include "LevelManager.h"

LevelManager::LevelManager(std::shared_ptr<World> world) : m_lvlsFile(), m_world{world} {
	m_lvlsFile.open("GameLevels.txt", std::ifstream::in);
}

std::shared_ptr<Objects> LevelManager::CreateObj(const char& x)
{
	switch (x)
	{
	case '@': ObjectFactory<StaticObjects>::instance().create("Pigs", *m_world->getWorld(), sf::Vector2f(620, WINDOW_HEIGHT - 110.f), sf::Vector2f(20.f, 0.f)); break;
	case '-': break;
	default:
		break;
	}
	return std::shared_ptr<Objects>();
}

std::vector<std::shared_ptr<Objects>> LevelManager::GetLevel()
{
	std::cout << " GetLevel() \n";

	std::deque<std::string> objDeq{ ReadLevel()};
	std::vector<std::shared_ptr<Objects>> objVec{};

	while (!objDeq.empty())
	{
		std::string temp = objDeq.front();
		objVec.emplace_back();
		objDeq.pop_front();
	}


	return std::vector<std::shared_ptr<Objects>>();
}


std::deque<std::string> LevelManager::ReadLevel()
{
	std::cout << "ReadLevel()" << std::endl;

	std::deque<std::string> objDeq;
	std::string temp;
	while (m_lvlsFile.is_open() && m_lvlsFile.good())
	{
		std::getline(m_lvlsFile, temp);
		if (temp.find("=") != std::string::npos) break;

		std::cout << "now read line " << temp << std::endl;
		if (!std::all_of(temp.begin(), temp.end(), [](const char &c) {return c == ' ' || isalnum(c) || isalnum(c); }))
			objDeq.push_back(temp);
	}
	return objDeq;
}