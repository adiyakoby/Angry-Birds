#pragma once

#include "Objects.h"



class Bird: public Objects
{
    //public Objects
public:

	Bird(std::shared_ptr<World> world,const sf::Vector2f &position, const sf::Vector2f& size, const int& index);
    virtual ~Bird() = default;
    
    virtual void objectUpdate();
    void applyForce(const sf::Vector2f& force);

    virtual void drawObject(sf::RenderWindow& window);
    void handleThrow(const float x, const float y);
    void setRangeVector(const sf::Vector2i& mouseLocation, sf::RenderWindow& w);
    bool isDragged() { return m_dragging; };
    void setPosition(const sf::Vector2f& pos);
    virtual void handleEvent(sf::Event& event, const sf::Vector2f& mouse);
    sf::Vector2f getPosition() const override;
    sf::Vector2f getBeginPosition() const { return dragStartPosition; };
    sf::Vector2f calculateThrow();
    void setOnRogatka(const bool& is) { m_onRogatka = is; m_body->SetEnabled(true); };
    bool isOnRogatka() const { return m_onRogatka; };
    float getBirdAngle() { return m_bird.getRotation(); };
    void gotHit() { m_hit = true; };
    bool isHit() const { return m_hit; };
    


protected:
    sf::CircleShape m_bird;
    virtual void rotate(const int& x) {};

private:
    int m_BirdType;
    bool m_onRogatka;
    bool m_dragging;
    bool m_hit;
    sf::Vector2f dragStartPosition;
    sf::Vector2f dragEndPosition;
     
    //private functions
    void initPhysicBody(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size)override;
    void initGraphicBody(const sf::Vector2f& size = {20.f, 0.f}) override;
};


