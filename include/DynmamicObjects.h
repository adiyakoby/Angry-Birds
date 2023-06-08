#pragma once

#include "Objects.h"


class DynamicObjects : public Objects
{
public:
	DynamicObjects() : m_hp(100) {}
	virtual ~DynamicObjects() =  default;

	virtual void drawObject(sf::RenderWindow& window) = 0;
	virtual void objectUpdate() = 0;

	int getHp() const { return m_hp; }
	void setHp(int damage) { m_hp -= damage; }

protected:
	b2Body* m_body;
private:
	int m_hp;
};


