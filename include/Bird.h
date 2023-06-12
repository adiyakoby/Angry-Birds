#pragma once

#include "Objects.h"



class Bird: public Objects
{
    //public Objects
public:
	Bird(b2World& world,const sf::Vector2f &position, const sf::Vector2f& size);
    virtual ~Bird() = default;
    
    virtual void objectUpdate();
    void applyForce(const sf::Vector2f& force);
    void drawObject(sf::RenderWindow& window);
    void handleThrow(const float x, const float y);
    void setRangeVector(const sf::Vector2i& mouseLocation, sf::RenderWindow& w);
    bool isDragged() { return m_dragging; };
    void setPosition(const sf::Vector2f& pos);
    void handleEvent(sf::Event& event, const sf::Vector2f& mouse);
    sf::Vector2f getPosition() const override;
    sf::Vector2f calculateThrow();

private:
    sf::CircleShape m_bird;
   
    bool m_dragging;
    sf::Vector2f dragStartPosition;
    sf::Vector2f dragEndPosition;
     
    //private functions
    void initPhysicBody(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size)override;
    void initGraphicBody(const sf::Vector2f& size = {20.f, 0.f}) override;
};

 static auto registerItBird = ObjectFactory<Bird>::instance().registerType(
     "Bird",
     [](b2World& world, const sf::Vector2f& position,const sf::Vector2f& size) -> std::unique_ptr<Bird>
     {
         return std::make_unique<Bird>(world, position, size);
     }
 );
