#include "MyContactListener.h"


void MyContactListener::BeginContact(b2Contact* contact)
{
	std::cout << "got contanct \n";
}


void MyContactListener::EndContact(b2Contact* contact)
{
}