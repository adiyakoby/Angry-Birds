#include "Ground.h"


Ground::Ground(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size) {
    initPhysicBody(world, position, size);
    initGraphicBody();
}


void Ground::initPhysicBody(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size) {
    /* NEED TO CHANGE TO CHAIN*/
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(size.x/2.f/SCALE, size.y / SCALE);
    m_body = world.CreateBody(&bodyDef);

    // Create Box2D ground shape
    b2PolygonShape groundshape;
    groundshape.SetAsBox(size.x / 2.f / SCALE, 25.f / SCALE); /* CHANGER 25 TO SIZE.Y */
     
    // Create Box2D fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundshape;
    fixtureDef.friction = 0.5f;
    m_body->CreateFixture(&fixtureDef);
}
void Ground::initGraphicBody(const sf::Vector2f& size) {
    b2Vec2 position = m_body->GetPosition();
    float angle = m_body->GetAngle();


    // IRRELEVENT -> Will read complete texture 
    m_ground.setFillColor(sf::Color::Blue);
    m_ground.setSize(sf::Vector2f(size.x, 50.f));
    m_ground.setOrigin(m_ground.getSize().x / 2.f, m_ground.getSize().y / 2.f);
    m_ground.setPosition(position.x * SCALE, position.y * SCALE);
    m_ground.setRotation(angle * 180.0f / b2_pi);
    
}

void Ground::drawObject(sf::RenderWindow &window)
{
    window.draw(m_ground);
}