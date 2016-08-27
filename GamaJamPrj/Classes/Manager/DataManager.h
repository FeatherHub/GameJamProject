#pragma once

#include "cocos2d.h"
USING_NS_CC;

//UIs
class JoyStick;
class Dig;
class Flag;
class TurnCounter;

//Object
class Character;

//Data
//struct 
class DataManager : public Node
{
public:
	CREATE_FUNC(DataManager);
	virtual bool init() override;

private:
	void CallUI(Ref* sender);

private:
	//UI
	JoyStick* m_pJoyStick;
	Dig* m_pBtnDig;
	Flag* m_pBtnFlag;
	TurnCounter* m_pTurnCounter;

	//Object
	Character* m_pCharacter;
};