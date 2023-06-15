#pragma once	

#include <memory>
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

template <typename OBJTYPE>
class ObjectFactory
{
public:
    using FuncType = std::unique_ptr<OBJTYPE>(*)(b2World& , const sf::Vector2f& , const sf::Vector2f&);

    static ObjectFactory<OBJTYPE>& instance();
    bool registerType(std::string type, FuncType func);

    std::unique_ptr<OBJTYPE> create(std::string type, b2World& world,  sf::Vector2f position, const sf::Vector2f& size) const;
 
private:
    ObjectFactory() = default;
    ObjectFactory(const ObjectFactory&) = delete;
    void operator=(const ObjectFactory&) = delete;

    std::unordered_map<std::string, FuncType> m_map;
};

template <typename OBJTYPE>
ObjectFactory<OBJTYPE>& ObjectFactory<OBJTYPE>::instance()
{
    static ObjectFactory<OBJTYPE> instance;
    return instance;
}

template <typename OBJTYPE>
bool ObjectFactory<OBJTYPE>::registerType(std::string type, FuncType func)
{
    m_map.emplace(type, func);
    return true;
}

template <typename OBJTYPE>
std::unique_ptr<OBJTYPE> ObjectFactory<OBJTYPE>::create(std::string type, b2World& world, sf::Vector2f position, const sf::Vector2f& size) const
{
    if (!m_map.contains(type)) return nullptr;
    return m_map.at(type)(world, position, size);
}