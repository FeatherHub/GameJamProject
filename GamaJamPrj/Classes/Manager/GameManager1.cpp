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
#include "Data/Constants2.h"
#include "Data/Mapdata.h"
#include "SimpleAudioEngine.h"

#include "Scene/SelectScene.h"
#include "Scene/MainScene.h"

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
	m_pRefBtnDig->setPosition(Constants2::DIG_POS);
	m_pRefBtnFlag = m_pDM->pBtnFlag;
	m_pRefBtnFlag->setPosition(Constants2::FLAG_POS);
	m_pRefTurnCounter = m_pDM->pTurnCounter;
	m_pRefTurnCounter->setPosition(Constants2::TURN_COUNTER_POS);
	m_pRefPlanetProgressJar = m_pDM->pPlanetProgressJar;
	m_pRefPlanetProgressJar->setPosition(Constants2::PLANET_PROGRESS_JAR_POS);

	//Data
	m_pRefCharPosMap = m_pDM->pCharPosMap;
	m_pRefDirDeltaPos = m_pDM->pDirDeltaPos;
	m_pRefObjectTypeMap = m_pDM->pObjectTypeMap;
	m_pRefNumberDataMap = m_pDM->pNumberDataMap;
	m_pRefSpriteMap = m_pDM->pSpriteMap;
	m_pRefMapMetaData = m_pDM->pMapMetaData;

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
		1.5f + Constants::VIEWPORT_LEFT_BOTTOM_Y + Constants::TILE_SIZE*Constants::VIEWPORT_HEIGHT_TILE_NUM));
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
			CharDig();
			break;
		case CHARACTER_ACTION::FLAG:
			CharFlag();
			break;
		case CHARACTER_ACTION::MOVE:
			CharMove();
			break;
		}

		int curGetHeart = m_pRefPlanetProgressJar->GetHeartNum();
		if (curGetHeart == m_pRefMapMetaData->heartNum)
		{
			return GAME_CODE::WIN;
		}

		int curLeftTurn = m_pRefTurnCounter->GetTurn();
		if (curLeftTurn == 0)
		{
			return GAME_CODE::LOSE;
		}
	}

	return GAME_CODE::NONE;
}

void GameManager::Lose()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Effect/over.wav ");

	UserDefault::getInstance()->setBoolForKey(PATH2::IS_START.c_str(), false);
	Scene* pscene = MainScene::createScene();
	TransitionScene* tr = TransitionProgressInOut::create(1.0f, pscene);
	Director::getInstance()->replaceScene(tr);
}

void GameManager::Win()
{
	// 턴카운트
	UserDefault::getInstance()->setIntegerForKey(PATH2::TURN_COUNT_KEY.c_str(), m_pRefTurnCounter->GetTurn());

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Effect/clear.wav ");

	UserDefault::getInstance()->setBoolForKey(PATH2::IS_CLEAR.c_str(), true);
	
	int type = UserDefault::getInstance()->getIntegerForKey(PATH2::NOW_STAGE_KEY.c_str());
	switch (type)
	{
	case 0:UserDefault::getInstance()->setBoolForKey(PATH::STAGE1_BOOL_KEY.c_str(), true); break;
	case 1:UserDefault::getInstance()->setBoolForKey(PATH::STAGE2_BOOL_KEY.c_str(), true); break;
	case 2:UserDefault::getInstance()->setBoolForKey(PATH::STAGE3_BOOL_KEY.c_str(), true); break;
	case 3:UserDefault::getInstance()->setBoolForKey(PATH::STAGE4_BOOL_KEY.c_str(), true); break;
	case 4:UserDefault::getInstance()->setBoolForKey(PATH::STAGE5_BOOL_KEY.c_str(), true); break;
	}
	
	Scene* pscene = SelectScene::createScene();
	TransitionScene* tr = TransitionProgressInOut::create(1.0f, pscene);
	Director::getInstance()->replaceScene(tr);
}
