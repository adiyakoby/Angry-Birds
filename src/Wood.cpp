#include "Wood.h"

Wood::Wood(std::shared_ptr<World> world, const sf::Vector2f position, const sf::Vector2f& size) : 
    StaticObjects(world, WOOD_HP, WOOD_SCORE), m_hit{false} {
    initPhysicBody(world, position, size);
    initGraphicBody(size);
}

void Wood::objectUpdate()
{
    b2Vec2 position = m_body->GetPosition();
    float angle = m_body->GetAngle();
    m_wood.setPosition(position.x * SCALE, position.y * SCALE);
    m_wood.setRotation(angle * 180.0f / b2_pi);
}

void Wood::drawObject(sf::RenderWindow& window)
{
    window.draw(m_wood);
}

void Wood::initPhysicBody(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x / SCALE, position.y / SCALE);
    bodyDef.linearDamping = 0.5f;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_body = world->getWorld()->CreateBody(&bodyDef);

    // Create Box2D rect shape
    b2PolygonShape shape;
    shape.SetAsBox(size.x / 2.f / SCALE, size.y / 2.f / SCALE);

    // Create Box2D fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.3f;
    m_body->CreateFixture(&fixtureDef);
	
}

void Wood::initGraphicBody(const sf::Vector2f& size) 
{
    m_wood.setTexture(&GameResources::getInstance().getWoodsTexture(0));
    m_wood.setSize(size);
    m_wood.setOrigin(size.x*0.5f , size.y * 0.5f);
    m_wood.setPosition(std::move(sf::Vector2f(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE)));
}

//to "register" the object in the Factory
static auto registerItWood = ObjectFactory<StaticObjects>::instance().registerType(
    "wood",
    [](std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size) -> std::unique_ptr<StaticObjects>
    {
        return std::make_unique<Wood>(world, position, size);
    }
);

void Wood::hitState()
{
    if (m_hit) return;
    m_wood.setTexture(&GameResources::getInstance().getWoodsTexture(2));
    m_hit = true;
}