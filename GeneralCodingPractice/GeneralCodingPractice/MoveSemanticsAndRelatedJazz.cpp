#include "MoveSemanticsAndRelatedJazz.h"

namespace movesemantics
{

void runMoveIntroduction()
{
	Entity entity(String("Prabha Shankar"));	//This requires a copy constructor within String class
												/* To create this Entity object, we had to do memory allocation twice (a deep copy)
												 * - 1. when creating the String object "Prabha Shankar"
												 * - 2. pass the String object in 1. and then copy that into another String object inside 
												 *		Entity class, i.e., Entity::m_name
												 * 
												 * Question: is there some way possible we can do with only a single memory allocation (maybe, a shallow copy)?
												 * In simpler words, is it possible to move the String object directly into Entity::m_name?
												 */
	entity.printName();

	std::cin.get();
}

}