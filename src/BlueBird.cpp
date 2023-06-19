#include "BlueBird.h"


BlueBird::BlueBird(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size) :
    Bird(world, position, size), m_world{ world}, isSplit{false}, m_state{normal} {
	 
	initGraphicBody(size);
}


void BlueBird::initGraphicBody(const sf::Vector2f& size ) {

	m_bird.setTexture(&GameResources::getInstance().getBirdTexture(2));
	m_bird.setRadius(size.x);
	m_bird.setOrigin(size.x, size.x);
	m_bird.setPosition(sf::Vector2f(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE));
}

void BlueBird::objectUpdate() {

    if (m_state == normal) {
        b2Vec2 position = m_body->GetPosition();
        float angle = m_body->GetAngle();
        m_bird.setPosition(position.x * SCALE, position.y * SCALE);
        m_bird.setRotation(angle * 180.0f / b2_pi);
    }
    else if (m_state == split) {
        for (auto& ea : m_split)
            ea->objectUpdate();
    }

}
void BlueBird::drawObject(sf::RenderWindow& w) {
    
    if (m_state == normal)
        w.draw(m_bird);
    else if (m_state == split) {
        for (auto& ea : m_split)
            ea->drawObject(w);
    }
}

void BlueBird::handleEvent(sf::Event& event, const sf::Vector2f& mouse) {

    switch (event.type) {

    case sf::Event::MouseButtonPressed:

        
        if (event.mouseButton.button == sf::Mouse::Left && !isSplit) {
            this->handleThrow(mouse.x, mouse.y);
            isSplit = true;
        }
        else if (event.mouseButton.button == sf::Mouse::Left && isSplit) {

            sf::Vector2f location = this->getPosition();
            location.y -= 50.f;
            for (auto& ea : m_split) {
                ea = std::make_unique<BlueBird>(m_world, location, sf::Vector2f(15.f, 0.f));
                location.y += 50.f;
            }
            isSplit = false;
            m_state = split;
        }

        break;
    case sf::Event::MouseButtonReleased:
       
        if (event.mouseButton.button == sf::Mouse::Left && isDragged()) {
            sf::Vector2f force = this->calculateThrow();
            this->applyForce(force);
        }
        break;


    }

}