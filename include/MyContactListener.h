#pragma once
#include <box2d/box2d.h>
#include <iostream>

class MyContactListener : public b2ContactListener
{
public:
	MyContactListener() = default;
	~MyContactListener() = default;

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

private:

};

