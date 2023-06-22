#include "Pig.h"

Pig::Pig(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size, arrData arr)
    : StaticObjects(world, arr.at(1), arr.at(2) ), m_hit{false}, m_textuerIndex{arr.at(0)}
{
    initPhysicBody(world, position, size);
    initGraphicBody(size);
    //setHp(2);
    
}


void Pig::initPhysicBody(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size)
{
    // Create Box2D body definition
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x / SCALE, position.y / SCALE);
    bodyDef.linearDamping = 0.9f;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_body = world->getWorld()->CreateBody(&bodyDef);

    // Create Box2D circle shape
    b2CircleShape shape;
    shape.m_radius = size.x / SCALE;

    // Create Box2D fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = getHp()*0.05f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.4f;
    m_body->CreateFixture(&fixtureDef);

}
void Pig::initGraphicBody(const sf::Vector2f& size)
{

    m_pig.setTexture(&GameResources::getInstance().getPigsTexture(m_textuerIndex));
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

void Pig::hitState() {
    if (!m_hit) {
        m_pig.setTexture(&GameResources::getInstance().getPigsTexture(1));
        m_hit = true;
    }
}

//to "register" the object in the Factory
static auto registerItPig = ObjectFactory<StaticObjects>::instance().registerType(
    "Pigs",
    [](std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size, arrData arr) -> std::unique_ptr<StaticObjects>
    {
        return std::make_unique<Pig>(world, position, size, arr);
    }
);