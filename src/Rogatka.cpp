#include "Rogatka.h"

Rogatka::Rogatka(b2World& world,const sf::Vector2f& position) {
    initPhysicRogatka(world, position);
    initGraphicRogatka();
    m_rogatkaSize = m_rogatka.getSize();
}

void Rogatka::initPhysicRogatka(b2World& world,const sf::Vector2f& position) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(position.x  /  SCALE, (position.y) / SCALE);
    m_body = world.CreateBody(&bodyDef);

    b2PolygonShape groundshape;
    groundshape.SetAsBox(5.f / SCALE, 60.f / 2.f / SCALE);

    // Create Box2D fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundshape;
    fixtureDef.friction = 0.5f;
    m_body->CreateFixture(&fixtureDef);
}


void Rogatka::initGraphicRogatka() {
    b2Vec2 position = m_body->GetPosition();
    float angle = m_body->GetAngle();
    m_rogatka.setTexture(&GameResources::getInstance().getRogatkaTexture(0));
    m_rogatka.setSize(sf::Vector2f(80.f, 120.f));
    m_rogatka.setOrigin(m_rogatka.getSize().x / 2.f, m_rogatka.getSize().y / 2.f);
    m_rogatka.setPosition(position.x * SCALE, position.y * SCALE);
    m_rogatka.setRotation(angle * 180.0f / b2_pi);
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