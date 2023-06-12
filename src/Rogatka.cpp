#include "Rogatka.h"

Rogatka::Rogatka(b2World& world,const sf::Vector2f& position, const sf::Vector2f& size ) {
    initPhysicBody(world, position, size);
    initGraphicBody(size);
    m_rogatkaSize = m_rogatka.getSize();
}

void Rogatka::initPhysicBody(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(position.x  /  SCALE, (position.y) / SCALE);
    m_body = world.CreateBody(&bodyDef);

    b2PolygonShape groundshape;
    groundshape.SetAsBox(size.x/2 / SCALE, size.y / 2.f / SCALE);

    // Create Box2D fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundshape;
    fixtureDef.friction = 0.5f;
    m_body->CreateFixture(&fixtureDef);
}


void Rogatka::initGraphicBody(const sf::Vector2f& size) {
    b2Vec2 position = m_body->GetPosition();
    float angle = m_body->GetAngle();
    m_rogatka.setTexture(&GameResources::getInstance().getRogatkaTexture(0));
    m_rogatka.setSize(sf::Vector2f(size.x*8, size.y*2));
    m_rogatka.setOrigin(m_rogatka.getSize().x / 2.f, m_rogatka.getSize().y / 2.f);
    m_rogatka.setPosition(position.x * SCALE, position.y * SCALE);
    m_rogatka.setRotation(angle * size.y*3 / b2_pi);
}


void Rogatka::drawObject(sf::RenderWindow& window) {

    window.draw(m_rogatka);
}

void Rogatka::ignoreRogatka() {
    m_body->SetEnabled(false);
}
void Rogatka::resetRogatka() {
    m_body->SetEnabled(true);
}