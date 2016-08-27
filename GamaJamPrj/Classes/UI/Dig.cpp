/*
2016. 8. 27
작성자 도인혁
*/

#include "Dig.h"
#include "Data\/Constants.h"

bool Dig::init(ccMenuCallback func)
{
	if (!Node::init())
	{
		return false;
	}

	this->func = func;
	generateDig();

	return true;
}

void Dig::generateDig()
{
	dig = Menu::create();
	this->addChild(dig);

	MenuItem* digItem = MenuItemImage::create(
		PATH::DIG_BASE + ".png",
		PATH::DIG_BASE + "_.png", func);

	digItem->setTag(Constants::TAG_DIG);
	digItem->setPosition(-100, -300);
	dig->addChild(digItem);
}