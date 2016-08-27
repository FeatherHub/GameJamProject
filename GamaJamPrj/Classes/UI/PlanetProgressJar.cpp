#include "PlanetProgressJar.h"
#include "SimpleAudioEngine.h"

bool PlanetProgressJar::init()
{
	if (Node::init() == false)
	{
		return false;
	}

	return true;
}
