#pragma once

#include "cocos2d.h"
#include "Utils\Macro.h"
#include "Data/Constants.h"

USING_NS_CC;

class TurnCounter : public Node
{
public :
	CREATE_FUNC_ARGS(TurnCounter);
	bool init(int stageTurn);
	void renewLabel();
	void LoseTurn(MAP_OBJECT_TYPE mot); 
	void BonusTurn();
	int GetTurn() { return m_curTurn; }
private:
	void generateData(int stageTurn);
	void generateLabel();
	void generateShovel();
private:
	CREATEWINSIZE;
	int m_curTurn;
	Label* m_lblTurn;
	Sprite* m_shovelSpr;
};