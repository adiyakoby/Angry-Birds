#include "LevelManager.h"

LevelManager::LevelManager(std::shared_ptr<World> world) : m_lvlsFile(), m_world{world} {
	m_lvlsFile.open("GameLevels.txt", std::ifstream::in);
}


void LevelManager::getNextLevel(std::vector<std::unique_ptr<Bird>> &birdsVec, std::vector<std::unique_ptr<StaticObjects>>& pigsVec, std::vector<std::unique_ptr<StaticObjects>> &objVec)
{
	if (!m_lvlsFile.is_open() || !m_lvlsFile.good()) exit(0);  // <- EXIT GAME IF LVLS FINISHED / ENDED

	std::deque<std::string> objDeq{ ReadBirds() };
	birdsVec = std::move(CreateBirds(objDeq));
	 
	objDeq = ReadLevel();
	CreateObj(objDeq, pigsVec, objVec);

}

void LevelManager::getSpecificLevel(const int& lvl, std::vector<std::unique_ptr<Bird>>& birdsVec, std::vector<std::unique_ptr<StaticObjects>>& pigsVec, std::vector<std::unique_ptr<StaticObjects>>& objVec)
{
	birdsVec.clear();
	pigsVec.clear();
	objVec.clear();

	m_lvlsFile.clear();
	m_lvlsFile.seekg(0);
	std::string temp{};
	while (m_lvlsFile.is_open() && m_lvlsFile.good())
	{
		std::getline(m_lvlsFile, temp);
		if (temp.find("Level " + std::to_string(lvl)) != std::string::npos)
			getNextLevel(birdsVec, pigsVec, objVec);
	}
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
		if(temp.find("Birds") != std::string::npos )objDeq.push_back(temp.substr(temp.find("Birds: ") + 7));
	}
	return objDeq;
}

std::vector<std::unique_ptr<Bird>> LevelManager::CreateBirds(std::deque<std::string>& objDeq)
{
	float deltaX{ 100.f };
	std::vector<std::unique_ptr<Bird>> tempVec;

	while (!objDeq.empty())
	{
		std::string line = objDeq.back();

		for (size_t i = 0; i < line.size(); i++)
		{
			switch (line.at(line.size()-i-1))
			{
			case 'R': tempVec.emplace_back(std::move(ObjectFactory<Bird>::instance().create("RedBird", m_world, sf::Vector2f(ROGATKA_X - deltaX, ROGATKA_Y - 100.f), sf::Vector2f(20.f, 0.f))));     break;
			case 'Y': tempVec.emplace_back(std::move(ObjectFactory<Bird>::instance().create("YellowBird", m_world, sf::Vector2f(ROGATKA_X - deltaX, ROGATKA_Y - 100.f), sf::Vector2f(20.f, 0.f))));  break;

			default: break;
			}
			deltaX += 50.f;


		}

		objDeq.pop_back();
	}

	return tempVec;
}

void LevelManager::CreateObj(std::deque<std::string> & objDeq, std::vector<std::unique_ptr<StaticObjects>>& pigsVec, std::vector<std::unique_ptr<StaticObjects>>& objVec)
{
	int xPos = WINDOW_WIDTH * 0.5;
	int yPos = 740-150;

	while (!objDeq.empty())
	{
		std::string line = objDeq.back();
		for (size_t i = 0; i < line.size(); i++)
		{
			switch (line.at(i))
			{
			case ' ': xPos += 100; break;
			case '@': pigsVec.emplace_back(std::move(ObjectFactory<StaticObjects>::instance().create("Pigs",
				m_world, sf::Vector2f(xPos, yPos), sf::Vector2f(20.f, 0.f))));
				xPos += 22;																							break;

			case '!': objVec.emplace_back(std::move(ObjectFactory<StaticObjects>::instance().create("wood",
				m_world, sf::Vector2f(xPos, yPos), sf::Vector2f(300.f, 40.f))));
				objVec.back()->rotate(90); xPos += 44;																break;

			case '-': objVec.emplace_back(std::move(ObjectFactory<StaticObjects>::instance().create("wood",
						m_world, sf::Vector2f(xPos , yPos), sf::Vector2f(300.f, 20.f))));   
				xPos += 303;																						break;

			default: break;
			}
			
			
		}
		yPos -= 300;
		xPos = WINDOW_WIDTH * 0.5;
		objDeq.pop_back();
	}
	
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

