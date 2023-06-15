
#include "YellowBird.h"

YellowBird::YellowBird(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size) : Bird(world, position, size), m_secondclick{ false } {
    
    //initPhysicBody(world, position, size);
    initGraphicBody(size);
}


void YellowBird::initGraphicBody(const sf::Vector2f& size) {
    m_bird.setTexture(&GameResources::getInstance().getBirdTexture(1));
    m_bird.setRadius(size.x);
    m_bird.setOrigin(size.x, size.x);
    m_bird.setPosition(sf::Vector2f(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE));
}


void YellowBird::handleEvent(sf::Event& event, const sf::Vector2f& mouse)
{
    switch (event.type) {
       
    case sf::Event::MouseButtonPressed:

        if (event.mouseButton.button == sf::Mouse::Left && m_secondclick && !isDragged()) {
          
            b2Vec2 force{m_body->GetLinearVelocity()};
            force.Normalize();
            force *= 3.f;
            this->applyForce(sf::Vector2f(force.x * SCALE , force.y * SCALE));
            m_secondclick = false;
        }
        if (event.mouseButton.button == sf::Mouse::Left) {
            this->handleThrow(mouse.x, mouse.y);
        }
        
        break;
    case sf::Event::MouseButtonReleased:
        if (event.mouseButton.button == sf::Mouse::Left && isDragged()) {
            sf::Vector2f force = this->calculateThrow();
            this->applyForce(force);
            m_secondclick = true;
        }

        break;


    }
}

//void YellowBird::handleEvent(sf::Event& event, const sf::Vector2f& mouse)
//{
//    switch (event.type) {
//
//    case sf::Event::MouseButtonPressed:
//
//        /*if (event.mouseButton.button == sf::Mouse::Left&& m_secondclick && !isDragged()) {
//
//            sf::Vector2f force{ this->getPosition() };
//            this->applyForce(force);
//            m_secondclick = false;
//        }*/
//        if (event.mouseButton.button == sf::Mouse::Left && !m_secondclick) {
//            this->handleThrow(mouse.x, mouse.y);
//            m_secondclick = true;
//            break;
//
//        }
//
//    case sf::Event::MouseButtonReleased:
//        if (event.mouseButton.button == sf::Mouse::Left && isDragged()) {
//            sf::Vector2f force = this->calculateThrow();
//            this->applyForce(force);
//        }
//
//        break;
//
//
//    }
//}