#include "LevelManager.h"

LevelManager::LevelManager(std::shared_ptr<World> world) : m_lvlsFile(), m_world{world} {
	m_lvlsFile.open("GameLevels.txt", std::ifstream::in);
}


void LevelManager::getNextLevel(std::vector<std::unique_ptr<Bird>> &birdsVec, std::vector<std::unique_ptr<StaticObjects>> &objVec)
{
	std::deque<std::string> objDeq{ ReadBirds() };
	birdsVec = std::move(CreateBirds(objDeq));

	objDeq = ReadLevel() ;
	objVec = std::move(CreateObj(objDeq));

}

std::deque<std::string> LevelManager::ReadBirds()
{
	std::deque<std::string> objDeq;
	std::string temp;

	while (m_lvlsFile.is_open() && m_lvlsFile.good())
	{
		std::getline(m_lvlsFile, temp);

		if (std::all_of(temp.begin(), temp.end(), [](const char& c) {return c == ' '; }))
			break;
		objDeq.push_back(temp.substr(temp.find("Birds: ") + 7));
	}
	return objDeq;
}

std::vector<std::unique_ptr<Bird>> LevelManager::CreateBirds(std::deque<std::string>& objDeq)
{
	int xPos = WINDOW_WIDTH * 0.5;
	int yPos = 740 - 150;
	std::vector<std::unique_ptr<Bird>> tempVec;

	while (!objDeq.empty())
	{
		std::string line = objDeq.back();

		for (size_t i = 0; i < line.size(); i++)
		{
			switch (line.at(i))
			{
			case 'R': tempVec.emplace_back(std::move(ObjectFactory<RedBird>::instance().create("RedBird", *m_world->getWorld(), sf::Vector2f(0, 0), sf::Vector2f(20.f, 0.f))));     break;
			case 'Y': tempVec.emplace_back(std::move(ObjectFactory<YellowBird>::instance().create("YellowBird", *m_world->getWorld(), sf::Vector2f(0, 0), sf::Vector2f(20.f, 0.f))));  break;

			default: break;
			}


		}
		yPos -= 300;
		xPos = WINDOW_WIDTH * 0.5;
		objDeq.pop_back();
	}

	return tempVec;
}

std::vector<std::unique_ptr<StaticObjects>> LevelManager::CreateObj(std::deque<std::string> & objDeq)
{
	int xPos = WINDOW_WIDTH * 0.5;
	int yPos = 740-150;
	std::vector<std::unique_ptr<StaticObjects>> tempVec;

	while (!objDeq.empty())
	{
		std::string line = objDeq.back();
		for (size_t i = 0; i < line.size(); i++)
		{
			switch (line.at(i))
			{
			case ' ': xPos += 100; break;
			case '@': tempVec.emplace_back(std::move(ObjectFactory<StaticObjects>::instance().create("Pigs",
						*m_world->getWorld(), sf::Vector2f(xPos, yPos), sf::Vector2f(20.f, 0.f))));     
				xPos += 22;																							break;

			case '!': tempVec.emplace_back(std::move(ObjectFactory<StaticObjects>::instance().create("wood",
				*m_world->getWorld(), sf::Vector2f(xPos, yPos), sf::Vector2f(300.f, 40.f))));			
				tempVec.back()->rotate(90); xPos += 44;																break;

			case '-': tempVec.emplace_back(std::move(ObjectFactory<StaticObjects>::instance().create("wood", 
						*m_world->getWorld(), sf::Vector2f(xPos , yPos), sf::Vector2f(300.f, 20.f))));   
				xPos += 303;																						break;

			default: break;
			}
			
			
		}
		yPos -= 300;
		xPos = WINDOW_WIDTH * 0.5;
		objDeq.pop_back();
	}
	
	return tempVec;
}

std::vector<std::unique_ptr<StaticObjects>> LevelManager::GetLevel()
{
	std::deque<std::string> objDeq{ ReadLevel()};
	std::vector<std::unique_ptr<StaticObjects>> objVec{ CreateObj(objDeq)};
	return objVec;
}


std::deque<std::string> LevelManager::ReadLevel()
{
	std::deque<std::string> objDeq;
	std::string temp;
	while (m_lvlsFile.is_open() && m_lvlsFile.good())
	{
		std::getline(m_lvlsFile, temp);
		if (temp.find("=") != std::string::npos) break;

		if (!std::all_of(temp.begin(), temp.end(), [](const char &c) {return c == ' ' || isalnum(c) || isalnum(c); }))
			objDeq.push_back(temp);
	}
	return objDeq;
}

