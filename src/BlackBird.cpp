#include "BlackBird.h"


float calculateDistance(const sf::Vector2f& pos1, const sf::Vector2f& pos2) {
    float deltaX = pos2.x - pos1.x;
    float deltaY = pos2.y - pos1.y;

    float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
    return distance;
}


BlackBird::BlackBird(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size)
    : Bird(world, position, size, 3), m_world{ world }, m_activated(false), m_exploded{ false }
{
    m_bombs.resize(4);
}


void BlackBird::handleEvent(sf::Event& event, const sf::Vector2f& mouse)
{
    switch (event.type) {

    case sf::Event::MouseButtonPressed:

        if (event.mouseButton.button == sf::Mouse::Left && m_activated) {
            setBombs();
            m_activated = false;
            explode();
        }

        if (event.mouseButton.button == sf::Mouse::Left) {
            this->handleThrow(mouse.x, mouse.y);
        }

        break;
    case sf::Event::MouseButtonReleased:

        if (event.mouseButton.button == sf::Mouse::Left && isDragged()) {
            sf::Vector2f force = this->calculateThrow();
            this->applyForce(force);
            m_activated = true;
        }
        break;
    }

}

void BlackBird::drawObject(sf::RenderWindow& w)
{
    if(!m_exploded)
        Bird::drawObject(w);
    std::cout << m_bird.getPosition().y << std::endl;
    if (m_exploded) {
        static sf::Clock clock;
        for (int i{}; i < m_bombs.size(); i++) {
            if (calculateDistance(sf::Vector2f(m_bombs.at(i)->GetPosition().x * SCALE,
                m_bombs.at(i)->GetPosition().y * SCALE), m_bird.getPosition()) > BOMB_DISTANCE) {
                m_world->getWorld()->DestroyBody(m_bombs.at(i));
                m_bombs.erase(m_bombs.begin() + i);
                i--;
            }
        }
        if(clock.getElapsedTime().asSeconds() > 3.f)
            m_body->SetLinearVelocity(b2Vec2(0.f, 0.f));
        w.draw(m_bird);
    }
}

void BlackBird::setBombs() {
    
    sf::Vector2f pos{};
    sf::Vector2f location = m_bird.getPosition();
    float radius = m_bird.getRadius();
    for (int i{}; i < m_bombs.size(); i++) {
        switch (i) {
        case 0:
            pos = sf::Vector2f(location.x + radius, location.y + radius);
            break;
        case 1:
            pos = sf::Vector2f(location.x - radius, location.y - radius);
            break;
        case 2:
            pos = sf::Vector2f(location.x + radius, location.y - radius);
            break;
        case 3:
            pos = sf::Vector2f(location.x - radius, location.y + radius);
            break;
        default:
            break;
        }
        PhysicBombBody(i, pos);
    }
}
void BlackBird::PhysicBombBody(const int index, const sf::Vector2f& position) {

    // Create Box2D body definition
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x / SCALE, position.y / SCALE);
    bodyDef.linearDamping = 0.7f;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(nullptr);
    m_bombs.at(index) = m_world->getWorld()->CreateBody(&bodyDef);

    // Create Box2D circle shape
    b2CircleShape shape;
    shape.m_radius = BOMB_SIZE / SCALE;

    // Create Box2D fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.f;
    fixtureDef.restitution = 0.f;
    m_bombs.at(index)->CreateFixture(&fixtureDef);
}
void BlackBird::setBombTexture()
{
    ;
}
void BlackBird::explode()
{
    m_exploded = true;
    b2Vec2 force = m_body->GetLinearVelocity();
    destroyedBody();
    m_body->SetEnabled(false);
    for (int i{}; i < m_bombs.size(); i++) {
        switch (i) {
        case 0:
            ;
            break;
        case 1:
            force *= -1.f;
            break;
        case 2:
            force.y *= -1.f;
            break;
        case 3: 
            force.x *= -1.f;
            break;
        }
        m_bombs.at(i)->SetLinearVelocity(force);
        m_bombs.at(i)->ApplyLinearImpulseToCenter(b2Vec2(force.x , force.y ), true);
    }
}

void BlackBird::destroyedBody() {
    m_body->SetEnabled(false);
}
//to "register" the object in the Factory
static auto registerItBlackBird = ObjectFactory<Bird>::instance().registerType(
    "BlackBird",
    [](std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size) -> std::unique_ptr<Bird>
    {
        return std::make_unique<BlackBird>(world, position, size);
    }
);
