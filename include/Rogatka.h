#pragma once

#include "StaticObjects.h"


class Rogatka:public StaticObjects
{
public:
	Rogatka(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size = sf::Vector2f{ 15.f, 80.f }, arrData arr = {0,0,0});
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
	sf::Vector2f m_rogatkaSize; //size of the rogatka;

	virtual void initPhysicBody(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size) ;
	virtual void initGraphicBody(const sf::Vector2f& size) ;
};

