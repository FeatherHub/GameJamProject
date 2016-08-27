#include "JoyStick.h"
#include "Data\Constants.h"

/*
2016. 8. 27
작성자 도인혁
*/

bool JoyStick::init(ccMenuCallback func)
{
	if (!Node::init())
	{
		return false;
	}
	this->func = func;
	generateJoyStick();

	return true;
}

void JoyStick::generateJoyStick()
{
	menu = Menu::create();
	this->addChild(menu);

	// TODO : 이 부분의 경우에는 후에 string 값을 받아야함

	for (int i = 0; i < Constants::TAG_JOYSTICK_NUM; i++)
	{
		MenuItem* stick = MenuItemImage::create(
			PATH::JOTSTICK_BASE + ".png",
			PATH::JOTSTICK_BASE + "_.png", func);

		stick->setTag(Constants::TAG_JOYSTICK_TOP + i);
		stick->setRotation(i * 90);
		menu->addChild(stick);
	}
}