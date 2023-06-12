#include "MyContactListener.h"


void MyContactListener::BeginContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    // Get the bodies involved in the contact
    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();


    Objects* first = reinterpret_cast<Objects*>(bodyA->GetUserData().pointer);
    Objects* second = reinterpret_cast<Objects*>(bodyB->GetUserData().pointer);

    handleCollision(*first, *second);
}


void handleCollision(Objects& obj_1, Objects& obj_2) {


    ;
}

void MyContactListener::EndContact(b2Contact* contact)
{
}