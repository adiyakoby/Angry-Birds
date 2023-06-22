#include "RedBird.h"


RedBird::RedBird(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size, const int& index)
    : Bird(world,position,size, index) 
{
}




//to "register" the object in the Factory
static auto registerItYellowBird = ObjectFactory<Bird>::instance().registerType(
    "RedBird",
    [](std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size, const int& index) -> std::unique_ptr<Bird>
    {
        return std::make_unique<RedBird>(world, position, size, index);
    }
);