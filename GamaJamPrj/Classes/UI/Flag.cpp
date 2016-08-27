/*
2016. 8. 27
작성자 도인혁
*/

#include "Flag.h"
#include "Data\/Constants.h"

bool Flag::init(ccMenuCallback func)
{
	if (!Node::init())
	{
		return false;
	}
	this->func = func;
	generateFlag();
}

void Flag::generateFlag()
{
	flag = Menu::create();
	this->addChild(flag);

	MenuItem* flagItem = MenuItemImage::create(
		Constants::FLAG_BASE_PATH + ".png",
		Constants::FLAG_BASE_PATH + "_.png", func);

	flagItem->setTag(Constants::TAG_FLAG_NUM);
	flag->addChild(flagItem);
}