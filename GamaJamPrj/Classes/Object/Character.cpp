#include "Character.h"

bool Character::init()
{
	if (Node::init() == false)
	{
		return false;
	}

	for (int i = 0; i < (int)CHARACTER_ACTION::ACTION_NUMBER; i++)
	{
		m_statusArr[i] = false;
	}

	m_sprite = Sprite::create(PATH::CHARACTER);
	addChild(m_sprite);

	return true;
}

void Character::Move(const Vec2& deltaPos)
{
	runAction(Sequence::create(
		CallFunc::create([&]() {m_statusArr[(int)CHARACTER_ACTION::MOVE] = true; }),
		//animation and move position,
		MoveBy::create(Constants::ANI_MOVE_TIME, deltaPos),
		CallFunc::create([&]() {m_statusArr[(int)CHARACTER_ACTION::MOVE] = false; }),
		nullptr));
}

void Character::Dig()
{
	runAction(Sequence::create(
		CallFunc::create([&]() {m_statusArr[(int)CHARACTER_ACTION::DIG] = true; }),
		//animation
		CallFunc::create([&]() {m_statusArr[(int)CHARACTER_ACTION::DIG] = false; }),
		nullptr));
}

void Character::Flag()
{
	runAction(Sequence::create(
		CallFunc::create([&]() {m_statusArr[(int)CHARACTER_ACTION::FLAG] = true; }),
		//animation
		CallFunc::create([&]() {m_statusArr[(int)CHARACTER_ACTION::FLAG] = false; }),
		nullptr));
}

CHARACTER_ACTION Character::GetCurrentAction()
{
	auto action = m_actionQueue.front();
	m_actionQueue.pop();

	return action;
}

bool Character::IsStatusRunning(CHARACTER_ACTION charAction)
{
	return m_statusArr[(int)charAction];
}
