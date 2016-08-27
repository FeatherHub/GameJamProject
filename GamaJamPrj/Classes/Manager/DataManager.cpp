#include "DataManager.h"
#include "MapDataLoader.h"

#include "Data/Constants.h"
#include "Data/Mapdata.h"

#include "UI/Dig.h"
#include "UI/Flag.h"
#include "UI/JoyStick.h"
#include "UI/TurnCounter.h"
#include "UI/PlanetProgressJar.h"

#include "Object/Character.h"
#include "Object//CameraMan.h"

bool DataManager::init()
{
	if (Node::init() == false)
	{
		return false;
	}

	//init ui
	pBtnDig = Dig::create(CC_CALLBACK_1(DataManager::CallUI, this));
	pBtnFlag = Flag::create(CC_CALLBACK_1(DataManager::CallUI, this));
	pJoyStick = JoyStick::create(CC_CALLBACK_1(DataManager::CallUI, this));
	pTurnCounter = TurnCounter::create();
	pPlanetProgressJar = PlanetProgressJar::create();

	//init data
	MapMetaData* pMapMetaData;
	ObjectTypeMap* pObjectTypeMap = nullptr;
	int* pNumberMap = nullptr;
	Sprite** pSpriteMap = nullptr;
	CharacterPosMap* pCharPosMap = nullptr;
	Vec2* pDirDeltaPos = nullptr;

	//init object
	pCharacter = Character::create();
	pCharacter->SetTurn(111111);

	pCameraMan = CameraMan::create();
	pCameraMan->SetMapMetaData(pMapMetaData);

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
		pCharacter->AddActionToQueue(CHARACTER_ACTION::MOVE);
		pCharacter->SetDirction(DIRECTION::UP);
		break;
	case Constants::TAG_JOYSTICK_BOTTOM:	
		pCharacter->AddActionToQueue(CHARACTER_ACTION::MOVE);
		pCharacter->SetDirction(DIRECTION::DOWN);
		break;
	case Constants::TAG_JOYSTICK_LEFT:		
		pCharacter->AddActionToQueue(CHARACTER_ACTION::MOVE);
		pCharacter->SetDirction(DIRECTION::LEFT);
		break;
	case Constants::TAG_JOYSTICK_RIGHT:		
		pCharacter->AddActionToQueue(CHARACTER_ACTION::MOVE);
		pCharacter->SetDirction(DIRECTION::RIGHT);
		break;
	case Constants::TAG_FLAG:			
		pCharacter->AddActionToQueue(CHARACTER_ACTION::FLAG);
		break;
	case Constants::TAG_DIG:			
		pCharacter->AddActionToQueue(CHARACTER_ACTION::DIG);
		break;
	}
}