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

#include <time.h>

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

	//init meta data
	pMapMetaData = MapDataLoader::GetMapMetaData();
	
	//init object
	pCameraMan = CameraMan::create();
	pCameraMan->SetMapMetaData(pMapMetaData);

	//init data
	/*
	Note : call after CameraMan initialized.
	*/
	InitSpriteMap();
	InitObjectTypeMap();
	
	/*
	Note : call after ObjectTypeMap initialized
	*/
	InitNumberDataMap();
	InitCharPosMap();
	InitDirDeltaPos();

	/*
	Note : setposition after InitCharPosMap()
	*/
	pCharacter = Character::create();

	//retain
	/*
	Note: addChild는 GameManager에서 한다
	*/
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

	pSpriteMap->map = new Sprite**[pSpriteMap->width];
	for (int i = 0; i < pSpriteMap->width; i++)
	{
		pSpriteMap->map[i] = new Sprite*[pSpriteMap->height];
	}

	for (int x = 0; x < pSpriteMap->width; x++)
	{
		for (int y = 0; y < pSpriteMap->height; y++)
		{
			pSpriteMap->map[x][y] = Sprite::create(pMapMetaData->tilePath);
			pSpriteMap->map[x][y]->setPosition(Vec2(x*Constants::TILE_SIZE, 
													y*Constants::TILE_SIZE));
			pSpriteMap->map[x][y]->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

			pCameraMan->addChild(pSpriteMap->map[x][y]);
		}
	}
}

void DataManager::InitObjectTypeMap()
{
	pObjectTypeMap = new ObjectTypeMap();
	pObjectTypeMap->width = pMapMetaData->width;
	pObjectTypeMap->height = pMapMetaData->height;
	pObjectTypeMap->tileSize = Constants::TILE_SIZE;

	pObjectTypeMap->map = new MAP_OBJECT_TYPE*[pObjectTypeMap->width];
	for (int i = 0; i < pObjectTypeMap->width; i++)
	{
		pObjectTypeMap->map[i] = new MAP_OBJECT_TYPE[pObjectTypeMap->height];
	}

	srand((unsigned)time(NULL));

	int heartNumToSeed = pMapMetaData->heartNum;
	while (heartNumToSeed > 0)
	{
		Vec2 randPoint = Vec2(rand() % pObjectTypeMap->height,
							rand() % pObjectTypeMap->width);

		if (pObjectTypeMap->map[(int)randPoint.x][(int)randPoint.y] !=
			MAP_OBJECT_TYPE::HEART)
		{
			pObjectTypeMap->map[(int)randPoint.x][(int)randPoint.y] =
				MAP_OBJECT_TYPE::HEART;

			heartNumToSeed--;
		}
		else
		{
			pObjectTypeMap->map[(int)randPoint.x][(int)randPoint.y] =
				MAP_OBJECT_TYPE::ROAD;
		}
	}
}

void DataManager::InitNumberDataMap()
{
	pNumberDataMap = new NumberDataMap();
	pNumberDataMap->width = pMapMetaData->width;
	pNumberDataMap->height = pMapMetaData->height;
	pNumberDataMap->map = new int*[pNumberDataMap->width];
	for (int i = 0; i < pNumberDataMap->width; i++)
	{
		pNumberDataMap->map[i] = new int[pNumberDataMap->height];
	}

	for (int x = 0; x < pNumberDataMap->width; x++)
	{
		for (int y = 0; y < pNumberDataMap->height; y++)
		{
			pNumberDataMap->map[x][y] = 0;
		}
	}

	for (int x = 0; x < pNumberDataMap->width; x++)
	{
		for (int y = 0; y < pNumberDataMap->height; y++)
		{
			//right
			if (x < pNumberDataMap->width - 1)
			{
				//just-right
				if (IsThereHeart(x + 1, y) == true)
					pNumberDataMap->map[x][y]++;

				//right-up
				if (y < pNumberDataMap->height - 1 ||
					IsThereHeart(x + 1, y + 1) == true)
					pNumberDataMap->map[x][y]++;

				//right-down
				if (y > 0 || IsThereHeart(x + 1, y - 1) == true)
					pNumberDataMap->map[x][y]++;
			}

			//left
			if (x > 0)
			{
				//just-left
				if (IsThereHeart(x - 1, y) == true)
					pNumberDataMap->map[x][y]++;
				//left-up
				if (y < pNumberDataMap->height - 1 ||
					IsThereHeart(x - 1, y + 1) == true)
					pNumberDataMap->map[x][y]++;
				//left-down
				if (y > 0 || IsThereHeart(x - 1, y - 1) == true)
					pNumberDataMap->map[x][y]++;
			}

			//up
			if (y < pNumberDataMap->height - 1 ||
				IsThereHeart(x, y + 1) == true)
				pNumberDataMap->map[x][y]++;
			//down
			if (y > 0 || IsThereHeart(x, y - 1) == true)
				pNumberDataMap->map[x][y]++;
		}
	}
}

bool DataManager::IsThereHeart(int x, int y)
{
	if (pObjectTypeMap->map[x][y] == MAP_OBJECT_TYPE::HEART)
		return true;
	else
		return false;
}

void DataManager::InitCharPosMap()
{
	pCharPosMap = new CharacterPosMap();
	pCharPosMap->width = pMapMetaData->width;
	pCharPosMap->height = pMapMetaData->height;
	pCharPosMap->pos = Vec2(pCharPosMap->width/2, pCharPosMap->height/2);
}

void DataManager::InitDirDeltaPos()
{
	pDirDeltaPos = new Vec2[(int)DIRECTION::DIR_NUM];
	pDirDeltaPos[(int)DIRECTION::DOWN] = Vec2(0, -Constants::TILE_SIZE);
	pDirDeltaPos[(int)DIRECTION::UP] = Vec2(0, Constants::TILE_SIZE);
	pDirDeltaPos[(int)DIRECTION::LEFT] = Vec2(-Constants::TILE_SIZE, 0);
	pDirDeltaPos[(int)DIRECTION::RIGHT] = Vec2(Constants::TILE_SIZE, 0);
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
