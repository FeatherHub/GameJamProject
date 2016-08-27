#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include <queue>
#include "Data/Constants.h"

/*
class JoyStick;
class BtnDig;
class BtnFlag;
class LblTurn;
*/

class Character : public Node
{
public:
	/*
	Don't forget call SetTurn
	*/
	CREATE_FUNC(Character);
	virtual bool init() override;
	
	/*
	Note : Assure to revert status not running when finished
	*/
	void Move(const Vec2& deltaPos);
	void Dig();
	void Flag(); 
	bool IsStatusRunning(CHARACTER_ACTION charAction);

	void AddActionToQueue(CHARACTER_ACTION ca) { m_actionQueue.push(ca); }
	bool ActionQueueEmpty() { return m_actionQueue.empty(); }
	CHARACTER_ACTION GetCurrentAction();

	DIRECTION GetDirection() { return m_direction; }
	void SetDirction(DIRECTION dir) { m_direction = dir; }

	void SetTurn(int turn) { m_turn = turn; }
	
	/*
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

	int m_turn = -1;

	Sprite* m_sprite;

	//UIs
	/*
	JoyStick* m_pRefJoyStick = nullptr;
	BtnFlag* m_pRefBtnFlag = nullptr;
	BtnDig* m_pRefBtnDig = nullptr;
	LblTurn* m_pRefLblTurn = nullptr;
	*/
};