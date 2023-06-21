#include "MyContactListener.h"
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>

#include "Ground.h"
#include "Wood.h"
#include "Rogatka.h"
#include "Pig.h"
#include "World.h"
#include "RedBird.h"
#include "YellowBird.h"

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
    pig.setDamage(bird.getBodyMass() * bird.getBodyVelocity().LengthSquared());
    //if (pig.getHp() <= 10) {
        static_cast<Pig&>(pig).hitState();
        std::cout << "in damage state\n";
    //}

    std::cout << pig.getHp()  <<std::endl;

}

void pigBird(Objects& pig, Objects& bird) {

    birdPig(bird, pig);
}

void birdWood(Objects& bird, Objects& wood) {
    wood.setDamage(bird.getBodyMass() * bird.getBodyVelocity().LengthSquared());

}

void woodBird(Objects& wood, Objects& bird) {
    birdWood(bird, wood);
}

void pigWood(Objects& pig, Objects& wood) {

    float dmg{ wood.getBodyMass() * wood.getBodyVelocity().LengthSquared() + pig.getBodyMass() * pig.getBodyVelocity().LengthSquared() };
    pig.setDamage(dmg);
    wood.setDamage(dmg);
    if(pig.getHp() <= 10)
        static_cast<Pig&>(pig).hitState();
    std::cout << pig.getHp() << std::endl;
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

    phm[Key(typeid(RedBird), typeid(Wood))] = &birdWood;
    phm[Key(typeid(Wood), typeid(RedBird))] = &woodBird;

    phm[Key(typeid(RedBird), typeid(Pig))] = &birdPig;
    phm[Key(typeid(Pig), typeid(RedBird))] = &pigBird;

    phm[Key(typeid(Pig), typeid(Wood))] = &pigWood;
    phm[Key(typeid(Wood), typeid(Pig))] = &woodPig;

    phm[Key(typeid(YellowBird), typeid(Pig))] = &birdPig;
    phm[Key(typeid(Pig), typeid(YellowBird))] = &pigBird;

    phm[Key(typeid(YellowBird), typeid(Wood))] = &birdWood;
    phm[Key(typeid(Wood), typeid(YellowBird))] = &woodBird;

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
        return;
    
    collisionFunc(object1, object2);
}

