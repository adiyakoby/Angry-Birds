
#include "Bird.h"
#include <cmath>
Bird::Bird(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size) : m_dragging{ false }
{
    initPhysicBody(world, position, size);
    initGraphicBody();
}


void Bird::initPhysicBody(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size)
{
    // Create Box2D body definition
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x / SCALE, position.y / SCALE);
    bodyDef.linearDamping = 0.7f;
    m_body = world.CreateBody(&bodyDef);

    // Create Box2D circle shape
    b2CircleShape shape;
    shape.m_radius = size.x / SCALE;

    // Create Box2D fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.5f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.4f;
    m_body->CreateFixture(&fixtureDef);

}
void Bird::initGraphicBody(const sf::Vector2f size)
{

    m_bird.setTexture(&GameResources::getInstance().getBirdTexture(0));
    m_bird.setRadius(size.x);
    m_bird.setOrigin(size.x, size.x);
    m_bird.setPosition(sf::Vector2f(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE));

}

void Bird::objectUpdate()
{
    b2Vec2 position = m_body->GetPosition();
    float angle = m_body->GetAngle();
    m_bird.setPosition(position.x * SCALE, position.y * SCALE);
    m_bird.setRotation(angle * 180.0f / b2_pi);
}   


void Bird::applyForce(const sf::Vector2f& force)
{
    // Finished the drag
    m_dragging = false;
    // Apply impulse force to the Box2D body
    b2Vec2 forceScaled{ force.x / SCALE, force.y / SCALE };
    //temp.Normalize();
    m_body->SetLinearVelocity(forceScaled);
    m_body->ApplyLinearImpulse(forceScaled , m_body->GetWorldCenter() , true);

}


void Bird::drawObject(sf::RenderWindow& window)
{
    //first is updating
    this->objectUpdate();
    window.draw(m_bird);
}

void Bird::handleThrow(const float x, const float y)
{
    if (m_bird.getGlobalBounds().contains(sf::Vector2f(x, y)))
    {
        m_dragging = true;
        dragStartPosition = sf::Vector2f(x, y);
    }
}
void Bird::setRangeVector(const sf::Vector2i& mouseLocation, sf::RenderWindow& w)
{
    sf::VertexArray line(sf::Lines, 2);
    line[0] = sf::Vertex(dragStartPosition, sf::Color::Green);
    line[1] = sf::Vertex(dragEndPosition, sf::Color::Green);
    w.draw(line);
    m_bird.setPosition(mouseLocation.x, mouseLocation.y);
    m_body->SetTransform(b2Vec2(mouseLocation.x / SCALE, mouseLocation.y / SCALE),  (dragStartPosition.y-mouseLocation.y) / SCALE);
    dragEndPosition.x = mouseLocation.x;
    dragEndPosition.y = mouseLocation.y;
}
sf::Vector2f Bird::calculateThrow()
{
    /*sf::Vector2f t{ dragStartPosition - dragEndPosition };
    std::cout << t.x << " " << t.y << std::endl;*/

    return sf::Vector2f(dragStartPosition - dragEndPosition);
}

void Bird::setPosition(const sf::Vector2f& pos) {

    b2Vec2 temp{ pos.x / SCALE , pos.y / SCALE };
    m_body->SetTransform(temp, 0.f);
    m_bird.setPosition(pos);
}

/*

   sf::VertexArray line(sf::Lines, 2);
    line[0] = sf::Vertex(dragStartPosition, sf::Color::Green);
    line[1] = sf::Vertex(dragEndPosition, sf::Color::Green);
*/