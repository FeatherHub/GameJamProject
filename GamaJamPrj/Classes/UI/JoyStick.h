#pragma once

/*
2016. 8. 27
�ۼ��� ������
*/
#include "cocos2d.h"
#include "Utils\/Macro.h"

USING_NS_CC;

class JoyStick : public Node
{
public :
	bool init(ccMenuCallback func);
	CREATE_FUNC_ARGS(JoyStick);
private:
	void generateJoyStick();

private:
	ccMenuCallback func;
	Menu* menu;
};