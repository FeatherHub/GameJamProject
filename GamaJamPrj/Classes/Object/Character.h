#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include <queue>
#include "Data/Constants.h"

class JoyStick;
class BtnDig;
class BtnFlag;
class LblTurn;

class Character : public Node
{
public:
	CREATE_FUNC(Character);
	virtual bool init() override;
	void Move(const Vec2& deltaPos);
	void Dig();
	void Flag(); 
	bool ActionQueueEmpty() { return m_actionQueue.empty(); }
	CHARACTER_ACTION GetCharAction();
	DIRECTION GetDirection() { return m_direction; }
	bool IsStatusRunning(CHARACTER_ACTION charAction);

	/*
	void SetTurn(int turn) { m_turn = turn; }
	void SetJoyStick(JoyStick* pJoyStick) { m_pRefJoyStick = pJoyStick; }
	void SetBtnDig(BtnDig* pBtnDig) { m_pRefBtnDig = pBtnDig; }
	void SetBtnFlag(BtnFlag* pBtnFlag) { m_pRefBtnFlag = pBtnFlag; }
	void SetLblTurn(LblTurn* pLblTurn) { m_pRefLblTurn = pLblTurn; }
	*/

private:	
	//status
	bool m_statusArr[(int)CHARACTER_ACTION::ACTION_NUMBER];
	DIRECTION m_direction = DIRECTION::NONE;
	std::queue<CHARACTER_ACTION> m_actionQueue;
	
	/*
	Don't forget initialize turn
	*/
	int m_turn = -1;

	//UIs
	/*
	JoyStick* m_pRefJoyStick = nullptr;
	BtnFlag* m_pRefBtnFlag = nullptr;
	BtnDig* m_pRefBtnDig = nullptr;
	LblTurn* m_pRefLblTurn = nullptr;
	*/
};