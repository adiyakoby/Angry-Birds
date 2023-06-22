#pragma once
#include "Bird.h"

class BlackBird : public Bird
{
public:
    BlackBird(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size);
    virtual ~BlackBird() = default;
    void handleEvent(sf::Event& event, const sf::Vector2f& mouse);

private:
    bool m_activated;
    float m_explosionRadius;
    float m_explosionForce;
    std::shared_ptr<World> m_world;
    std::array<b2Body*,4> m_bombs;
    void explode();
    void setBombs();
    void PhysicBombBody(const int index, const sf::Vector2f& position);
};
