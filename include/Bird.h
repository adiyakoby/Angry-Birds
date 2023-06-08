#pragma once

#include "DynmamicObjects.h"



class Bird: public DynamicObjects
{
    //public Objects
public:
	Bird(b2World& world,const sf::Vector2f &position);
    virtual ~Bird() = default;
    
    virtual void objectUpdate();
    void applyForce(const sf::Vector2f& force);
    void drawObject(sf::RenderWindow& window);
    void handleThrow(const float x, const float y);
    void setRangeVector(const sf::Vector2i&mouseLocation);
    bool isDragged() { return m_dragging; };
    sf::Vector2f calculateThrow();
private:
    sf::CircleShape m_bird;
    //b2Body* m_body;
   
    bool m_dragging;
    sf::Vector2f dragStartPosition;
    sf::Vector2f dragEndPosition;
     
    //private functions
    void initPhysicBody(b2World& world, const sf::Vector2f& position);
    void initGraphicBody();
};


