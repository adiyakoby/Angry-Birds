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


/*

class Bird {
public:
    Bird(b2World& world, const sf::Vector2f& position) {
        // Create Box2D body definition
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(position.x / SCALE, position.y / SCALE);
        bodyDef.linearDamping = 0.5f;
        body = world.CreateBody(&bodyDef);

        // Create Box2D circle shape
        b2CircleShape shape;
        shape.m_radius = 20.0f / SCALE;

        // Create Box2D fixture definition
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.f;
        fixtureDef.friction = 0.3f;
        fixtureDef.restitution = 0.5f;
        body->CreateFixture(&fixtureDef);


        // Create SFML circle shape
        float size = 20.f;
        circle.setRadius(size);
        circle.setOrigin(size, size);
        circle.setPosition(position);
        //circle.setFillColor(sf::Color::Red);

        t.loadFromFile("redbird.png");
        circle.setTexture(&t);
    }

    void update() {
        // Update SFML circle position and rotation based on Box2D body
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();
        circle.setPosition(position.x * SCALE, position.y * SCALE);
        circle.setRotation(angle * 180.0f / b2_pi);
    }

    void applyForce(const sf::Vector2f& force) {
        // Apply impulse force to the Box2D body
        body->ApplyLinearImpulse(b2Vec2(force.x / SCALE, force.y / SCALE), body->GetWorldCenter(), true);

    }

    sf::CircleShape circle;
    b2Body* body;
    sf::Texture t;
};


*/
