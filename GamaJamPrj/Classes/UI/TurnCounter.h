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
	void LoseTurn() { turn--; }
	void BonusTurn() { turn+=2; }
	int GetTurn() { return turn; }
private:
	void generateLabel();
private:
	Label label;
	int turn;
};