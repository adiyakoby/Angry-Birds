#include "LevelManager.h"

LevelManager::LevelManager(std::shared_ptr<World> world) : m_lvlsFile(), m_world{world} {
	m_lvlsFile.open("GameLevels.txt", std::ifstream::in);
}

std::vector<std::shared_ptr<Objects>> LevelManager::CreateObj(std::deque<std::string> & objDeq)
{
	int xPos = 500;
	int yPos = WINDOW_HEIGHT;
	std::vector<std::shared_ptr<Objects>> tempVec;

	while (!objDeq.empty())
	{
		std::string line = objDeq.front();
		for (size_t i = 0; i < line.size(); i++)
		{
			switch (line.at(i))
			{
			case '@': tempVec.emplace_back(std::move(ObjectFactory<StaticObjects>::instance().create("Pigs",
						*m_world->getWorld(), sf::Vector2f(xPos+=30, yPos), sf::Vector2f(20.f, 0.f))));                     break;
			case '!':
			case '-': tempVec.emplace_back(std::move(ObjectFactory<StaticObjects>::instance().create("wood", 
						*m_world->getWorld(), sf::Vector2f(xPos += 300, yPos), sf::Vector2f(300.f, 20.f))));
				if (line.at(i) == '!') tempVec.back()->rotate(90);
																														break;

			default:
				break;
			}
			
		}
		
		objDeq.pop_front();
	}
	
	return tempVec;
}

std::vector<std::shared_ptr<Objects>> LevelManager::GetLevel()
{
	std::cout << " GetLevel() \n";

	std::deque<std::string> objDeq{ ReadLevel()};
	std::vector<std::shared_ptr<Objects>> objVec{ CreateObj(objDeq)};

	return objVec;
	//while (!objDeq.empty())
	//{
	//	std::string temp = objDeq.front();
	//	objVec.emplace_back();
	//	objDeq.pop_front();
	//}	
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