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

	m_callback = func;

	generateDig();

	return true;
}

void Dig::generateDig()
{
	m_menuDig = Menu::create();
	addChild(m_menuDig);

	MenuItem* digItem = MenuItemImage::create(
		PATH::DIG_BASE + ".png",
		PATH::DIG_BASE + "_.png", m_callback);

	digItem->setTag(Constants::TAG_DIG);
	digItem->setPosition(-100, -300);
	m_menuDig->addChild(digItem);
}