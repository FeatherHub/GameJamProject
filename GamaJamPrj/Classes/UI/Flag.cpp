/*
2016. 8. 27
작성자 도인혁
*/

#include "Flag.h"
#include "Data\/Constants.h"

bool Flag::init(ccMenuCallback callback)
{
	if (!Node::init())
	{
		return false;
	}
	m_callback = callback;

	generateFlag();

	return true;
}

void Flag::generateFlag()
{
	m_menuFlag = Menu::create();
	addChild(m_menuFlag);

	MenuItem* flagItem = MenuItemImage::create(
		PATH::FLAG_BASE + ".png",
		PATH::FLAG_BASE + "_.png", m_callback);
	flagItem->setPosition(-80, -280);
	flagItem->setTag(Constants::TAG_FLAG);
	m_menuFlag->addChild(flagItem);
}