#include "RedBird.h"


RedBird::RedBird(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size) : Bird(world,position,size) {

    initGraphicBody(size);
}


void RedBird::initGraphicBody(const sf::Vector2f& size)
{
    m_bird.setTexture(&GameResources::getInstance().getBirdTexture(0));
    m_bird.setRadius(size.x);
    m_bird.setOrigin(size.x, size.x);
    m_bird.setPosition(sf::Vector2f(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE));
}