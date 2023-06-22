#pragma once
#include "Bird.h"

class BlackBird : public Bird
{
public:
    BlackBird(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size, arrData arr = {3,BIRD_HP,0});
    virtual ~BlackBird() = default;
    void handleEvent(sf::Event& event, const sf::Vector2f& mouse);
    void drawObject(sf::RenderWindow& w);
private:
    bool m_activated;
    bool m_exploded;
    std::shared_ptr<World> m_world;
    std::vector<b2Body*> m_bombs;
    std::array<sf::CircleShape, 2> m_bombImage;
    void setBombTexture();
    void explode();
    void setBombs();
    void PhysicBombBody(const int index, const sf::Vector2f& position);
    void destroyedBody();
};
