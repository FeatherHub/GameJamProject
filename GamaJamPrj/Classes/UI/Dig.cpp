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
}

void Dig::generateDig()
{
	dig = Menu::create();
	this->addChild(dig);

	MenuItem* digItem = MenuItemImage::create(
		Constants::DIG_BASE_PATH + ".png",
		Constants::DIG_BASE_PATH + "_.png", func);

	digItem->setTag(Constants::TAG_DIG_NUM);
	dig->addChild(digItem);
}