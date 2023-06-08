
#include "StaticObjects.h"


class Rogatka:public StaticObjects
{
public:
	Rogatka(b2World& world,const sf::Vector2f &position);
	virtual ~Rogatka() = default;

	virtual void drawObject(sf::RenderWindow& window);
	sf::Vector2f getPostion() { return m_rogatka.getPosition(); };

	void ignoreRogatka();
	void resetRogatka();
private:
	sf::RectangleShape m_rogatka;
	
	//size of the rogatka;
	sf::Vector2f m_rogatkaSize;

	void initPhysicRogatka(b2World& world,  const sf::Vector2f& position);
	void initGraphicRogatka();
};

