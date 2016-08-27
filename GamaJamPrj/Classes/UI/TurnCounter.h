#pragma once

#include "cocos2d.h"
#include "Utils\Macro.h"

USING_NS_CC;

class TurnCounter : public Node
{
public :
	CREATE_FUNC_ARGS(TurnCounter);
	bool init(int stageTurn);
	void renewLabel();
	void LoseTurn() { curTurn--; }
	void BonusTurn();
	int GetTurn() { return curTurn; }
private:
	void generateData(int stageTurn);
	void generateLabel();
	void generateShovel();
private:
	CREATEWINSIZE;
	Label* label;
	int curTurn;
	Sprite* shovel;

};