#include "World.h"
#include <iostream>
#include"GameResources.h"

World::World(/*const b2Vec2 graviry*/) {

	m_world = std::make_unique<b2World>(b2Vec2(0.f, 10.8f));
    setFrame();
}


void World::step(const float timestep,const int32 velocity,const int32 positionIteration) {
	m_world->Step(timestep, velocity, positionIteration);
}

void World::setFrame() {

    m_worldFrame.emplace_back(setCorner(Left));
    m_worldFrame.emplace_back(setCorner(Top));
    m_worldFrame.emplace_back(setCorner(Right));
	
}

b2Body* World::setCorner(Position position) {

    
    float width{25.f}, height{25.f};
    b2Body* body;
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    

    b2PolygonShape boxshape;
    switch (position) {
    case Left :
        bodyDef.position.Set(-width / SCALE, (WINDOW_HEIGHT) / SCALE);
        boxshape.SetAsBox(width / 2.f / SCALE, WINDOW_HEIGHT / SCALE);
        break;
    case Top:
        bodyDef.position.Set(WINDOW_WIDTH / 2.f / SCALE, -height / SCALE);
        boxshape.SetAsBox(WINDOW_WIDTH / 2.f / SCALE, height / SCALE);
        break;
    case Right:

        bodyDef.position.Set((GameResources::getInstance().getGroundTexture(0).getSize().x*3 + width) / SCALE, (WINDOW_HEIGHT) / 2.f / SCALE);
        boxshape.SetAsBox(width / 2 / SCALE, WINDOW_HEIGHT / SCALE);
        break;
    default:
        // Code for default case (if index does not match any of the above cases)
        break;
    }

    body = m_world->CreateBody(&bodyDef);
    //// Create Box2D fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxshape;
    fixtureDef.friction = 0.5f;
    body->CreateFixture(&fixtureDef);
    m_worldFrame.emplace_back(body);
    return body;
}