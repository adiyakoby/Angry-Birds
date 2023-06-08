#pragma once

#include "DynmamicObjects.h"


class Wood:public DynamicObjects
{
public:
	Wood(b2World& world, const sf::Vector2f position, const sf::Vector2f& size);
	virtual ~Wood() = default;
	
	void objectUpdate() override;
	void drawObject(sf::RenderWindow& window) override;
private:
	sf::RectangleShape m_wood;
	void initPhysicBody(b2World& world,const  sf::Vector2f postion, const sf::Vector2f size);
	void initGraphicBody(const sf::Vector2f size);
};

static auto registerItWood = ObjectFactory<DynamicObjects>::instance().registerType(
	"wood",
	[](b2World& world, const sf::Vector2f& position, const sf::Vector2f& size) -> std::unique_ptr<DynamicObjects>
	{
		return std::make_unique<Wood>(world, position,size);
	}
);