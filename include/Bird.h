#pragma once

#include "DynmamicObjects.h"



class Bird: public DynamicObjects
{
    //public Objects
public:
	Bird(b2World& world,const sf::Vector2f &position, const sf::Vector2f& size);
    virtual ~Bird() = default;
    
    virtual void objectUpdate();
    void applyForce(const sf::Vector2f& force);
    void drawObject(sf::RenderWindow& window);
    void handleThrow(const float x, const float y);
    void setRangeVector(const sf::Vector2i&mouseLocation);
    bool isDragged() { return m_dragging; };
    void setPosition(const sf::Vector2f& pos);

    sf::Vector2f calculateThrow();

private:
    sf::CircleShape m_bird;
   
    bool m_dragging;
    sf::Vector2f dragStartPosition;
    sf::Vector2f dragEndPosition;
     
    //private functions
    void initPhysicBody(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size);
    void initGraphicBody();
};

 static auto registerItBird = ObjectFactory<DynamicObjects>::instance().registerType(
     "Bird",
     [](b2World& world, const sf::Vector2f& position,const sf::Vector2f& size) -> std::unique_ptr<DynamicObjects>
     {
         return std::make_unique<Bird>(world, position, size);
     }
 );
