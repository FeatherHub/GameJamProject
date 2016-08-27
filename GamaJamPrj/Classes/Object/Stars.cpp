#include "Stars.h"

bool Stars::init(ccMenuCallback func)
{
	if (!Node::init())
	{
		return false;
	}
	this->func = func;
	generateStars();
}

void Stars::generateStars()
{
	stars = Menu::create();
	this->addChild(stars);

	MenuItem* star
}