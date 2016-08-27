#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include <queue>
#include "Data/Constants.h"

class Character : public Node
{
public:
	CREATE_FUNC(Character);
	virtual bool init() override;
	
	void Move(const Vec2& deltaPos);
	void Dig();
	void Flag(); 
	bool IsStatusRunning(CHARACTER_ACTION charAction);

	void AddActionToQueue(CHARACTER_ACTION ca) { m_actionQueue.push(ca); }
	bool ActionQueueEmpty() { return m_actionQueue.empty(); }
	CHARACTER_ACTION GetCurrentAction();

	DIRECTION GetDirection() { return m_direction; }
	void SetDirction(DIRECTION dir) { m_direction = dir; }

private:	
	bool m_statusArr[(int)CHARACTER_ACTION::ACTION_NUMBER];
	DIRECTION m_direction = DIRECTION::NONE;
	std::queue<CHARACTER_ACTION> m_actionQueue;

	Sprite* m_sprite;
};