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
	m_pRefJoyStick->setPosition(Constants::JOYSTICK_POS);
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
	m_pRefCameraMan = m_pDM->pCameraMan;

	m_pRefCharacter = m_pDM->pCharacter;
	const Vec2 charPosOnMap{ m_pRefCharPosMap->pos * Constants::TILE_SIZE };
	const Vec2 deltaChangedCameraPos{ m_pRefCameraMan->GetChangedCameraDeltaPos() };
	const Vec2 toViewPort{ 0, (int)Constants::VIEWPORT_LEFT_BOTTOM_Y };
	const Vec2 characterMoveUp{ 0, 20 };
	m_pRefCharacter->setPosition(
		charPosOnMap - deltaChangedCameraPos + toViewPort + characterMoveUp);

	//1. Map
	addChild(m_pRefCameraMan);

	//2. Black curtain
	Sprite* blackBottom = Sprite::create(PATH::BLACK);
	blackBottom->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	blackBottom->setPosition(Vec2(0, Constants::VIEWPORT_LEFT_BOTTOM_Y - 0.5f));
	addChild(blackBottom);

	Sprite* blackTop = Sprite::create(PATH::BLACK);
	blackTop->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	blackTop->setPosition(Vec2(0,
		3 + Constants::VIEWPORT_LEFT_BOTTOM_Y + Constants::TILE_SIZE*Constants::VIEWPORT_HEIGHT_TILE_NUM));
	addChild(blackTop);

	//3. Characer
	addChild(m_pRefCharacter);

	//4. UI
	addChild(m_pRefBtnDig);
	addChild(m_pRefBtnFlag);
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

		//카메라나 캐릭터가
		//이미 다른 action을 수행하고 있으면 
		//입력 버리고 함수수행 안 함
		if (m_pRefCharacter->IsStatusRunning(CHARACTER_ACTION::DIG) ||
			m_pRefCharacter->IsStatusRunning(CHARACTER_ACTION::FLAG) ||
			m_pRefCharacter->IsStatusRunning(CHARACTER_ACTION::MOVE) ||
			m_pRefCameraMan->IsMoving())
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
