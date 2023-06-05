#include "Ground.h"


Ground::Ground(b2World& world) {
    initPhysicBody(world);
    initGraphicBody();
}


void Ground::initPhysicBody(b2World& world) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(WINDOW_WIDTH / 2 / SCALE, (WINDOW_HEIGHT ) / SCALE);
    m_body = world.CreateBody(&bodyDef);

    // Create Box2D ground shape
    b2PolygonShape groundshape;
    groundshape.SetAsBox(WINDOW_WIDTH / 2 / SCALE, 25.f / SCALE);

    // Create Box2D fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundshape;
    fixtureDef.friction = 0.5f;
    m_body->CreateFixture(&fixtureDef);
}
void Ground::initGraphicBody() {
    b2Vec2 position = m_body->GetPosition();
    float angle = m_body->GetAngle();

    m_ground.setFillColor(sf::Color::Blue);
    m_ground.setSize(sf::Vector2f(WINDOW_WIDTH, 50.f));
    m_ground.setOrigin(m_ground.getSize().x / 2.f, m_ground.getSize().y / 2.f);
    m_ground.setPosition(position.x * SCALE, position.y * SCALE);
    m_ground.setRotation(angle * 180.0f / b2_pi);
}

void Ground::drawObject(sf::RenderWindow &window) {
    window.draw(m_ground);
}