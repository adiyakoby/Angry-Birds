#include "MyContactListener.h"
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "Bird.h"
#include "Ground.h"
#include "Wood.h"
#include "Rogatka.h"
#include "Pig.h"
#include "World.h"

void MyContactListener::BeginContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    // Get the bodies involved in the contact
    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();

    if (reinterpret_cast<World*>(bodyA->GetUserData().pointer) == nullptr ||
        reinterpret_cast<World*>(bodyB->GetUserData().pointer) == nullptr)
        return;

    Objects* first = reinterpret_cast<Objects*>(bodyA->GetUserData().pointer);
    Objects* second = reinterpret_cast<Objects*>(bodyB->GetUserData().pointer);

    handleCollision(*first, *second);
}

namespace {//begin namespace

//-------------HIT FUNCTIONS-----------
void birdPig(Objects& bird, Objects& pig) {


    Bird& getbird = dynamic_cast<Bird&>(bird);
    Pig& getpig = dynamic_cast<Pig&>(pig);

    getpig.setDamage(2);
    getpig.hitState();
    std::cout << "a collision\n";
}

void pigBird(Objects& pig, Objects& bird) {

    birdPig(bird, pig);
}

void birdWood(Objects& bird, Objects& wood) {

    Bird& getbird = dynamic_cast<Bird&>(bird);
    Wood& getwood = dynamic_cast<Wood&>(wood);

    getwood.setDamage(1);

}
void woodBird(Objects& wood, Objects& bird) {
    birdWood(bird, wood);
}

void pigWood(Objects& pig, Objects& wood) {

    Pig& getpig = dynamic_cast<Pig&>(pig);
    Wood& getwood = dynamic_cast<Wood&>(wood);
    getpig.setDamage(1);
    getpig.hitState();
    getwood.setDamage(1);
}

void woodPig(Objects& wood, Objects& pig) {
    pigWood(pig, wood);
}
//-----------END HIT FUNCTION------------

using HitFunctionPtr = std::function<void(Objects&, Objects&)>;
// typedef void (*HitFunctionPtr)(GameObject&, GameObject&);
using Key = std::pair<std::type_index, std::type_index>;
// std::unordered_map is better, but it requires defining good hash function for pair
using HitMap = std::map<Key, HitFunctionPtr>;

HitMap initializeCollisionMap()
{
    HitMap phm;
    phm[Key(typeid(Bird), typeid(Pig))] = &birdPig;
    phm[Key(typeid(Pig), typeid(Bird))] = &pigBird;
    phm[Key(typeid(Bird), typeid(Wood))] = &birdWood;
    phm[Key(typeid(Wood), typeid(Bird))] = &woodBird;
    phm[Key(typeid(Pig), typeid(Wood))] = &pigWood;
    phm[Key(typeid(Wood), typeid(Pig))] = &woodPig;

    //...
    return phm;
}
HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
{
    static HitMap collisionMap = initializeCollisionMap();
    auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
    if (mapEntry == collisionMap.end())
    {
        return nullptr;
    }
    return mapEntry->second;
}



}//end namespace

void handleCollision(Objects& object1, Objects& object2) {

    auto collisionFunc = lookup(typeid(object1), typeid(object2));
    if (!collisionFunc)
    {
        return;
    }
    collisionFunc(object1, object2);
}

//void MyContactListener::EndContact(b2Contact* contact)
//{
//}