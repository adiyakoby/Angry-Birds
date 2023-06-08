#pragma once
#include "StaticObjects.h"

class Ground : public StaticObjects
{
public:
	Ground(b2World& world, const sf::Vector2f& position);
	 ~Ground() = default;

	
	void drawObject(sf::RenderWindow& window) override;
private:
	sf::RectangleShape m_ground;

	//init functions
	void initPhysicBody(b2World& world);
	void initGraphicBody();
	
};

//static auto registerItGround = ObjectFactory<StaticObjects>::instance().registerType(
//	"ground",
//	[](b2World& world, const sf::Vector2f& position, const sf::Vector2f& size) -> std::unique_ptr<StaticObjects>
//	{
//		return std::make_unique<Ground>(world, position, size);
//	}
//);