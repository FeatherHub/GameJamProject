#include "JoyStick.h"
#include "Data\Constants.h"

/*
2016. 8. 27
작성자 도인혁
*/

bool JoyStick::init(ccMenuCallback callback)
{
	if (!Node::init())
	{
		return false;
	}

	m_callback = callback;

	generateJoyStick();

	return true;
}

void JoyStick::generateJoyStick()
{
	m_menuJoyStick = Menu::create();
	addChild(m_menuJoyStick);

	for (int i = 0; i < Constants::TAG_JOYSTICK_NUM; i++)
	{
		MenuItem* stick = MenuItemImage::create(
			PATH::JOTSTICK_BASE + ".png",
			PATH::JOTSTICK_BASE + "_.png", m_callback);

		stick->setTag(Constants::TAG_JOYSTICK_TOP + i);
		stick->setRotation(i * 90);

		stick->setPosition(Vec2(0, 0));
		if (i==0 || i==2)
			stick->setPosition(Vec2(0, Constants::JOYSTICK_DISTANCE + -Constants::JOYSTICK_DISTANCE  * i));
		else
			stick->setPosition(Vec2(Constants::JOYSTICK_DISTANCE*2 + -Constants::JOYSTICK_DISTANCE*i , 0));

		m_menuJoyStick->addChild(stick);
	}
}