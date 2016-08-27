#include "DataManager.h"
#include "Data/Constants.h"

#include "UI/Dig.h"
#include "UI/Flag.h"
#include "UI/JoyStick.h"
#include "UI/TurnCounter.h"
#include "UI/PlanetProgressJar.h"

#include "Object/Character.h"

bool DataManager::init()
{
	if (Node::init() == false)
	{
		return false;
	}

	m_pBtnDig = Dig::create(CC_CALLBACK_1(DataManager::CallUI, this));
	m_pBtnFlag = Flag::create(CC_CALLBACK_1(DataManager::CallUI, this));
	m_pJoyStick = JoyStick::create(CC_CALLBACK_1(DataManager::CallUI, this));
	m_pTurnCounter = TurnCounter::create();

	m_pCharacter = Character::create();
	m_pCharacter->SetTurn(111111);

	return true;
}

/*
UI 콜백을 받아서 상황에 맞게 호출함
2016. 8. 27
작성자 : 도인혁
*/
void DataManager::CallUI(Ref* sender)
{
	auto type = (Menu*)sender;
	switch (type->getTag())
	{
	case Constants::TAG_JOYSTICK_TOP:		
		m_pCharacter->AddActionToQueue(CHARACTER_ACTION::MOVE);
		m_pCharacter->SetDirction(DIRECTION::UP);
		break;
	case Constants::TAG_JOYSTICK_BOTTOM:	
		m_pCharacter->AddActionToQueue(CHARACTER_ACTION::MOVE);
		m_pCharacter->SetDirction(DIRECTION::DOWN);
		break;
	case Constants::TAG_JOYSTICK_LEFT:		
		m_pCharacter->AddActionToQueue(CHARACTER_ACTION::MOVE);
		m_pCharacter->SetDirction(DIRECTION::LEFT);
		break;
	case Constants::TAG_JOYSTICK_RIGHT:		
		m_pCharacter->AddActionToQueue(CHARACTER_ACTION::MOVE);
		m_pCharacter->SetDirction(DIRECTION::RIGHT);
		break;
	case Constants::TAG_FLAG:			
		m_pCharacter->AddActionToQueue(CHARACTER_ACTION::FLAG);
		break;
	case Constants::TAG_DIG:			
		m_pCharacter->AddActionToQueue(CHARACTER_ACTION::DIG);
		break;
	}
}