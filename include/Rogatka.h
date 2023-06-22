#pragma once

#include "StaticObjects.h"


class Rogatka:public StaticObjects
{
public:
	Rogatka(std::shared_ptr<World> world,const sf::Vector2f &position, const sf::Vector2f& size = sf::Vector2f{ 10.f, 60.f }, const int& index = 0);
	virtual ~Rogatka() = default;

	void objectUpdate()override {}
	virtual void drawObject(sf::RenderWindow& window);
	sf::Vector2f getPosition() const override { return m_rogatka.getPosition(); };
	void rotate(const int& x) override { ; };
	void hitState() override { ; };
	void ignoreRogatka();
	void resetRogatka();
private:
	sf::RectangleShape m_rogatka;
	
	int m_textureIndex;
	//size of the rogatka;
	sf::Vector2f m_rogatkaSize;

	//void initPhysicRogatka(b2World& world,  const sf::Vector2f& position);
	//void initGraphicRogatka();

	virtual void initPhysicBody(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size) ;
	virtual void initGraphicBody(const sf::Vector2f& size) ;
};

