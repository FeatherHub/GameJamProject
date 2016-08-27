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
//	m_pRefCharacter->setPosition();
	m_pRefCameraMan = m_pDM->pCameraMan;
//	m_pRefCameraMan->setPosition();

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

GAME_CODE GameManager::update()
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
			return CharDig();
			break;
		case CHARACTER_ACTION::FLAG:
			return CharFlag();
			break;
		case CHARACTER_ACTION::MOVE:
			return CharMove();
			break;
		}
	}

	return GAME_CODE::NONE;
}

void GameManager::Lose()
{

}

void GameManager::Win()
{

}
