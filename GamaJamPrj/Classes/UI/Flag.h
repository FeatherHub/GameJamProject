#pragma once

/*
	2016. 8. 27 
	�ۼ��� ������
*/

#include "cocos2d.h"
#include "Utils\/Macro.h"

USING_NS_CC;

class Flag : public Node
{
public :
	bool init(ccMenuCallback callback);
	CREATE_FUNC_ARGS(Flag);
private:
	void generateFlag();

private:
	ccMenuCallback m_callback;
	Menu* m_menuFlag;
};