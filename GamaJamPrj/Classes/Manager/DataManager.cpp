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
	pBtnDig = Dig::create(CC_CALLBACK_1(DataManager::ControllerUICallback, this));
	pBtnFlag = Flag::create(CC_CALLBACK_1(DataManager::ControllerUICallback, this));
	pJoyStick = JoyStick::create(CC_CALLBACK_1(DataManager::ControllerUICallback, this));
	pTurnCounter = TurnCounter::create();
	pPlanetProgressJar = PlanetProgressJar::create();

	//init data
	MapMetaData* pMapMetaData = MapDataLoader::GetMapMetaData();
	
	//init object
	pCharacter = Character::create();
	pCharacter->SetTurn(111111);

	pCameraMan = CameraMan::create();
	pCameraMan->SetMapMetaData(pMapMetaData);

	/*
	Note : call after CameraMan initialized.
	*/
	InitSpriteMap();
	InitObjectTypeMap();
	InitNumberDataMap();

	//retain
	pBtnFlag->retain();
	pBtnDig->retain();
	pBtnFlag->retain();
	pJoyStick->retain();
	pTurnCounter->retain();
	pPlanetProgressJar->retain();

	pCharacter->retain();
	pCameraMan->retain();
	
	return true;
}

void DataManager::InitSpriteMap()
{
	pSpriteMap = new SpriteMap();
	pSpriteMap->width = pMapMetaData->width;
	pSpriteMap->height = pMapMetaData->height;

	//동적 할당
	pSpriteMap->map = new Sprite**[pSpriteMap->width];
	for (int i = 0; i < pSpriteMap->width; i++)
	{
		pSpriteMap->map[i] = new Sprite*[pSpriteMap->height];
	}
	
	//타일 생성
	for (int x = 0; x < pSpriteMap->width; x++)
	{
		for (int y = 0; y < pSpriteMap->height; y++)
		{
			pSpriteMap->map[x][y] = Sprite::create(pMapMetaData->tilePath);
			pSpriteMap->map[x][y]->setPosition(Vec2(x*Constants::TILE_SIZE, 
													y*Constants::TILE_SIZE));
			pCameraMan->addChild(pSpriteMap->map[x][y]);
		}
	}
}

void DataManager::InitObjectTypeMap()
{
	CharacterPosMap* pCharPosMap = nullptr;

}

void DataManager::InitNumberDataMap()
{

	Vec2* pDirDeltaPos = nullptr;

}

/*
	UI 콜백을 받아서 상황에 맞게 호출함
	2016. 8. 27
	작성자 : 도인혁
*/
void DataManager::ControllerUICallback(Ref* sender)
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