#include "GuideLine.h"

GuideLine& GuideLine::getInstance()
{
	static GuideLine guideline;
	return guideline;
}

GuideLine::GuideLine()
{ 
    ;
}


void GuideLine::initPhysicBody()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 0.7f;
    bodyDef.position.Set(ROGATKA_X / SCALE, ROGATKA_Y - 50.f / SCALE);
    b2Body* body = m_world->getWorld()->CreateBody(&bodyDef);
    m_bodies.push_back(body);

    // Create Box2D circle shape
    b2CircleShape shape;
    shape.m_radius = 20.f / SCALE;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = BIRD_HP * 0.1f;
    fixtureDef.isSensor = true;
    body->CreateFixture(&fixtureDef);
}


void GuideLine::initGraphicBody()
{
    m_guideline.emplace_back();
    m_guideline.back().setFillColor(sf::Color::Black);
    m_guideline.back().setRadius(5.f);
    m_guideline.back().setOrigin(2.5f, 2.5f);
}

void GuideLine::setWorld(std::shared_ptr<World> world)
{
    m_world = world;

}

void GuideLine::drawGuideLine(sf::RenderWindow& window)
{
    for (size_t i = 0; i < m_bodies.size() ; i++)
    {
        m_guideline.at(i).setPosition(m_bodies.at(i)->GetPosition().x * SCALE, m_bodies.at(i)->GetPosition().y * SCALE);
        window.draw(m_guideline.at(i));
    }
}

void GuideLine::setPosition(const sf::Vector2f& pos)
{
    
    b2Vec2 dir{ (ROGATKA_X - pos.x) * 20.f / SCALE, (ROGATKA_Y - 50.f - pos.y) * 20.f / SCALE };

    initPhysicBody();
    initGraphicBody();

    m_bodies.back()->SetTransform({ pos.x / SCALE, pos.y / SCALE }, 0);
    m_bodies.back()->SetLinearVelocity(dir);

    
}
