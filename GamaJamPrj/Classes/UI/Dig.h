#pragma once

/*
	2016. 8. 27 
	작성자 도인혁
*/

#include "cocos2d.h"
#include "Utils\/Macro.h"

USING_NS_CC;

class Dig : public Node
{
public:
	bool init(ccMenuCallback func);
	CREATE_FUNC_ARGS(Dig);
private:
	void generateDig();

private:
	ccMenuCallback m_callback;
	Menu* m_menuDig;
};