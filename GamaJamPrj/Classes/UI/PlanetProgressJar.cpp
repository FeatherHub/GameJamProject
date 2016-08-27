#include "PlanetProgressJar.h"

bool PlanetProgressJar::init()
{
	if (Node::init() == false)
	{
		return false;
	}

	return true;
}
