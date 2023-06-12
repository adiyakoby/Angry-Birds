#pragma once

#include "StaticObjects.h"


class Wood:public StaticObjects
{
public:
	Wood(b2World& world, const sf::Vector2f position, const sf::Vector2f& size);
	virtual ~Wood() = default;
	
	void objectUpdate() override;
	void drawObject(sf::RenderWindow& window) override;
	sf::Vector2f getPosition() const override { return m_wood.getPosition(); }
private:
	sf::RectangleShape m_wood;
	void initPhysicBody(b2World& world,const sf::Vector2f& postion, const sf::Vector2f& size)override;
	void initGraphicBody(const sf::Vector2f& size)override;
};

static auto registerItWood = ObjectFactory<StaticObjects>::instance().registerType(
	"wood",
	[](b2World& world, const sf::Vector2f& position, const sf::Vector2f& size) -> std::unique_ptr<StaticObjects>
	{
		return std::make_unique<Wood>(world, position,size);
	}
);