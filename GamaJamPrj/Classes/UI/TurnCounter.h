#pragma once

#include "cocos2d.h"
#include "Utils\Macro.h"
#include "Data/Constants.h"

USING_NS_CC;

class TurnCounter : public Node
{
public :
	CREATE_FUNC_ARGS(TurnCounter);
	bool init();
	void renewLabel();
	void LoseTurn(MAP_OBJECT_TYPE mot); 
	void BonusTurn();
	int GetTurn() { return curTurn; }
private:
	void generateLabel();
private:
	Label label;
	int curTurn;
};