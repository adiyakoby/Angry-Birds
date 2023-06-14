#include "Pig.h"

Pig::Pig(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size) 
{
    initPhysicBody(world, position, size);
    initGraphicBody(size);
}


void Pig::initPhysicBody(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size)
{
    // Create Box2D body definition
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x / SCALE, position.y / SCALE);
    bodyDef.linearDamping = 0.9f;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_body = world.CreateBody(&bodyDef);

    // Create Box2D circle shape
    b2CircleShape shape;
    shape.m_radius = size.x / SCALE;

    // Create Box2D fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.9f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.4f;
    m_body->CreateFixture(&fixtureDef);

}
void Pig::initGraphicBody(const sf::Vector2f& size)
{

    m_pig.setTexture(&GameResources::getInstance().getPigsTexture(0));
    m_pig.setRadius(size.x);
    m_pig.setOrigin(size.x, size.x);
    m_pig.setPosition(sf::Vector2f(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE));

}

void Pig::objectUpdate()
{
    b2Vec2 position = m_body->GetPosition();
    float angle = m_body->GetAngle();
    m_pig.setPosition(position.x * SCALE, position.y * SCALE);
    m_pig.setRotation(angle * 180.0f / b2_pi);
}

void Pig::drawObject(sf::RenderWindow& window)
{
    window.draw(m_pig);
}