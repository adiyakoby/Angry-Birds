#pragma once

#include "StaticObjects.h"


class Rogatka:public StaticObjects
{
public:
	Rogatka(b2World& world,const sf::Vector2f &position, const sf::Vector2f& size = sf::Vector2f{ 10.f, 60.f });
	virtual ~Rogatka() = default;

	void objectUpdate()override {}
	virtual void drawObject(sf::RenderWindow& window);
	sf::Vector2f getPosition() const override { return m_rogatka.getPosition(); };
	void rotate(const int& x) override { ; };

	void ignoreRogatka();
	void resetRogatka();
private:
	sf::RectangleShape m_rogatka;
	
	//size of the rogatka;
	sf::Vector2f m_rogatkaSize;

	//void initPhysicRogatka(b2World& world,  const sf::Vector2f& position);
	//void initGraphicRogatka();

	virtual void initPhysicBody(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size) ;
	virtual void initGraphicBody(const sf::Vector2f& size) ;
};

