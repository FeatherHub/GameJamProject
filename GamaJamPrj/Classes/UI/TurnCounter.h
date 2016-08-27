#pragma once

#include "cocos2d.h"
#include "Utils\Macro.h"

USING_NS_CC;

class TurnCounter : public Node
{
public :
	CREATE_FUNC_ARGS(TurnCounter);
	bool init();
	void renewLabel();
private:
	void generateLabel();
private:
	Label label;
	int turn;
};