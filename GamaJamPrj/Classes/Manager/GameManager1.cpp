#include "GameManager.h"
#include "DataManager.h"

#include "UI/Dig.h"
#include "UI/Flag.h"
#include "UI/JoyStick.h"
#include "UI/TurnCounter.h"
#include "UI/PlanetProgressJar.h"

#include "Object/Character.h"
#include "Object/CameraMan.h"

#include "Data/Constants.h"
#include "Data/Mapdata.h"

bool GameManager::init()
{
	if (Node::init() == false)
	{
		return false;
	}
	
	m_pDM = DataManager::create();
	addChild(m_pDM);

	//UI
	m_pRefJoyStick = m_pDM->pJoyStick;
	m_pRefBtnDig = m_pDM->pBtnDig;
	m_pRefBtnFlag = m_pDM->pBtnFlag;
	m_pRefTurnCounter = m_pDM->pTurnCounter;
	m_pRefPlanetProgressJar = m_pDM->pPlanetProgressJar;

	//Data
	m_pRefCharPosMap = m_pDM->pCharPosMap;
	m_pRefDirDeltaPos = m_pDM->pDirDeltaPos;
	m_pRefObjectTypeMap = m_pDM->pObjectTypeMap;
	m_pRefNumberDataMap = m_pDM->pNumberDataMap;

	//Object
	m_pRefCharacter = m_pDM->pCharacter;
	m_pRefCameraMan = m_pDM->pCameraMan;
	
	//addChild
	
	addChild(m_pRefBtnDig);
	addChild(m_pRefBtnFlag);
	addChild(m_pRefCameraMan);
	addChild(m_pRefCharacter);
	addChild(m_pRefJoyStick);
	addChild(m_pRefPlanetProgressJar);
	addChild(m_pRefTurnCounter);

	return true;
}

void GameManager::update(float delta)
{
	while (m_pRefCharacter->ActionQueueEmpty() == false)
	{
		CHARACTER_ACTION action = m_pRefCharacter->GetCurrentAction();

		//이미 다른 action을 수행하고 있으면 
		//입력 버리고 함수수행 안 함
		if (m_pRefCharacter->IsStatusRunning(CHARACTER_ACTION::DIG) ||
			m_pRefCharacter->IsStatusRunning(CHARACTER_ACTION::FLAG) ||
			m_pRefCharacter->IsStatusRunning(CHARACTER_ACTION::MOVE))
		{
			continue;
		}

		switch (action)
		{
		case CHARACTER_ACTION::DIG:
			CharDig();
			break;
		case CHARACTER_ACTION::FLAG:
			CharFlag();
			break;
		case CHARACTER_ACTION::MOVE:
			CharMove();
			break;
		}
	}
}

void GameManager::CharMove()
{
	const auto& charPos = m_pRefCharacter->getPosition();
	const auto& charDir = m_pRefCharacter->GetDirection();
	const auto& moveDelta = m_pRefDirDeltaPos[(int)charDir];
	const auto& movedPos = charPos + moveDelta;

	//TODO: 움직임 유효하지 않는 상황에서 애니메이션으로 반응을 해주자
	
	//맵 바깥으로 빠졌나갔다
	if (movedPos.x > m_pRefObjectTypeMap->width ||
		movedPos.y > m_pRefObjectTypeMap->height ||
		movedPos.x < 0 || movedPos.y < 0)
	{
		return;
	}

	//벽과 충돌 했다
	int charXPos = m_pRefCharPosMap->pos.x;
	int charYPos = m_pRefCharPosMap->pos.y;
	if (m_pRefObjectTypeMap->map[charXPos][charYPos] == MAP_OBJECT_TYPE::WALL)
	{
		return;
	}

	/*
	Note : 캐릭터의 위치와 캐릭터 맵에서의 캐릭터 위치를 갱신한다
	*/
	m_pRefCharacter->Move(moveDelta);
	m_pRefCharPosMap->UpdatePos(charDir);

	m_pRefCameraMan->Move(moveDelta);
}

void GameManager::CharDig()
{
	int charXPos = m_pRefCharPosMap->pos.x;
	int charYPos = m_pRefCharPosMap->pos.y;
	auto objectType = m_pRefObjectTypeMap->map[charXPos][charYPos];

	switch (objectType)
	{
	case MAP_OBJECT_TYPE::ROAD:
		OnRoad();
		break;
	case MAP_OBJECT_TYPE::HEART:
		OnHeart();
		break;
	case MAP_OBJECT_TYPE::NUMBER:
		OnNumber();
		break;
	}
}

void GameManager::CharFlag()
{
	int charXPos = m_pRefCharPosMap->pos.x;
	int charYPos = m_pRefCharPosMap->pos.y;
	auto objectType = m_pRefObjectTypeMap->map[charXPos][charYPos];

	if (objectType == MAP_OBJECT_TYPE::FLAG_ON_HEART ||
		objectType == MAP_OBJECT_TYPE::FLAG_ON_NUMBER ||
		objectType == MAP_OBJECT_TYPE::FLAG_ON_ROAD)
	{
		//Character -> 깃발 뽑기 애니메이션 //일하고 있어
		m_pRefObjectTypeMap->map[charXPos][charYPos] = (MAP_OBJECT_TYPE)
			((int)objectType - (int)MAP_OBJECT_TYPE::FLAG_DELTA);
	}
	else if(objectType == MAP_OBJECT_TYPE::HEART ||
		objectType == MAP_OBJECT_TYPE::NUMBER || 
		objectType == MAP_OBJECT_TYPE::ROAD)
	{
		//Character -> 깃발 꼽기 애니메이션 //일하고 있어
		m_pRefObjectTypeMap->map[charXPos][charYPos] = (MAP_OBJECT_TYPE)
			((int)objectType + (int)MAP_OBJECT_TYPE::FLAG_DELTA);
	}
}