#include "JoyStick.h"
#include "Data\Constants.h"

/*
2016. 8. 27
�ۼ��� ������
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

	// TODO : �� �κ��� ��쿡�� �Ŀ� string ���� �޾ƾ���

	for (int i = 0; i < Constants::TAG_JOYSTICK_NUM; i++)
	{
		MenuItem* stick = MenuItemImage::create(
			PATH::JOTSTICK_BASE + ".png",
			PATH::JOTSTICK_BASE + "_.png", func);

		stick->setTag(Constants::TAG_JOYSTICK_TOP + i);
		stick->setRotation(i * 90);
		
		stick->setPosition(Vec2(0, 0));
		if (i==0 || i==2)
			stick->setPosition(Vec2(0, Constants::JOYSTICK_DISTANCE + -Constants::JOYSTICK_DISTANCE  * i));
		else
			stick->setPosition(Vec2(Constants::JOYSTICK_DISTANCE*2 + -Constants::JOYSTICK_DISTANCE*i , 0));

		menu->addChild(stick);
	}
}