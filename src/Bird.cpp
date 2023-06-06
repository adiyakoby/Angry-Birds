
#include "Bird.h"

Bird::Bird(b2World& world) : m_dragging{ false } {

    initPhysicBody(world);
    initGraphicBody();
}


void Bird::initPhysicBody(b2World& world) {
    // Create Box2D body definition
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(100.f / SCALE, 100.f / SCALE);
    bodyDef.linearDamping = 0.5f;
    m_body = world.CreateBody(&bodyDef);
   
    // Create Box2D circle shape
    b2CircleShape shape;
    shape.m_radius = 20.0f / SCALE;

    // Create Box2D fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.5f;
    m_body->CreateFixture(&fixtureDef);

}
void Bird::initGraphicBody() {
	
    m_bird.setTexture(&GameResources::getInstance().getBirdTexture(0));
    float size = 20.f;
    m_bird.setRadius(size);
    m_bird.setOrigin(size, size);
    m_bird.setPosition(sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y));
    
}

void Bird::objectUpdate() {
    b2Vec2 position = m_body->GetPosition();
    float angle = m_body->GetAngle();
    m_bird.setPosition(position.x * SCALE, position.y * SCALE);
    m_bird.setRotation(angle * 180.0f / b2_pi);
}

void Bird::applyForce(const sf::Vector2f &force) {
    
    // Finished the drag
    m_dragging = false;
    // Apply impulse force to the Box2D body
    m_body->ApplyLinearImpulse(b2Vec2(force.x / SCALE, force.y / SCALE), m_body->GetWorldCenter(), true);
}


void Bird::drawObject(sf::RenderWindow& window) {

    //first is updating
    this->objectUpdate();
    window.draw(m_bird);
}

void Bird::handleThrow(const float x, const float y) {
    if (m_bird.getGlobalBounds().contains(sf::Vector2f(x, y))) {
        m_dragging = true;
        dragStartPosition = m_bird.getPosition();
    }
}
void Bird::setRangeVector(const sf::Vector2i &mouseLocation) {
    m_bird.setPosition(mouseLocation.x,mouseLocation.y);
    m_body->SetTransform(b2Vec2(mouseLocation.x / SCALE, mouseLocation.y / SCALE), 0.0f);
    dragEndPosition.x = mouseLocation.x;
    dragEndPosition.y = mouseLocation.y;
}
sf::Vector2f Bird::calculateThrow() {
    return (dragStartPosition - dragEndPosition);
}
