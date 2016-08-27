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

GAME_CODE GameManager::CharMove()
{
	//Character is in World Space
	const auto& charPos = m_pRefCharacter->getPosition();
	const auto& charDir = m_pRefCharacter->GetDirection();
	const auto& moveDelta = m_pRefDirDeltaPos[(int)charDir];

	const auto& charMapPos = m_pRefCharPosMap->pos;
	const auto mapRightEdgeIdx = m_pRefCharPosMap->width - 1;
	const auto mapTopEdgeIdx = m_pRefCharPosMap->height - 1;

	if (mapTopEdgeIdx - charMapPos.y >= 2 ||
		charMapPos.y >= 2 ||
		mapRightEdgeIdx - charMapPos.x >= 2 ||
		charMapPos.x >= 2)
	{
		bool res = m_pRefCameraMan->Move(moveDelta);
		if (res == true)
		{
			m_pRefCharPosMap->UpdatePos(charDir);
			return GAME_CODE::NONE;
		}
	}

	//TODO: 움직임 유효하지 않는 상황에서 애니메이션으로 반응을 해주자

	const auto& movedPos = charPos + moveDelta;
	//맵 바깥으로 빠졌나갔다
	if (movedPos.x >= Constants::VIEWPORT_WIDTH ||
		movedPos.y >= Constants::VIEWPORT_HEIGHT + Constants::VIEWPORT_LEFT_BOTTOM_Y ||
		movedPos.x < 0 || movedPos.y  < Constants::VIEWPORT_LEFT_BOTTOM_Y)
	{
		return GAME_CODE::NONE;
	}
	
	/*
	//벽과 충돌 했다
	int charXPos = m_pRefCharPosMap->pos.x;
	int charYPos = m_pRefCharPosMap->pos.y;
	if (m_pRefObjectTypeMap->map[charXPos][charYPos] == MAP_OBJECT_TYPE::WALL)
	{
		return GAME_CODE::NONE;
	}
	*/

	/*
	Note : 캐릭터의 위치와 캐릭터 맵에서의 캐릭터 위치를 갱신한다
	*/
	m_pRefCharacter->Move(moveDelta);
	m_pRefCharPosMap->UpdatePos(charDir);

	return GAME_CODE::NONE;
}

GAME_CODE GameManager::CharDig()
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

	return GAME_CODE::NONE;
}

GAME_CODE GameManager::CharFlag()
{
	int x = m_pRefCharPosMap->pos.x;
	int y = m_pRefCharPosMap->pos.y;
	auto objectType = m_pRefObjectTypeMap->map[x][y];

	if (objectType == MAP_OBJECT_TYPE::FLAG_ON_HEART ||
		objectType == MAP_OBJECT_TYPE::FLAG_ON_NUMBER ||
		objectType == MAP_OBJECT_TYPE::FLAG_ON_ROAD)
	{
		//Character -> 깃발 뽑기 애니메이션 + 일하고 있어

		m_pRefSpriteMap->map[x][y]->removeAllChildren();

		m_pRefObjectTypeMap->map[x][y] = (MAP_OBJECT_TYPE)
			((int)objectType - (int)MAP_OBJECT_TYPE::FLAG_DELTA);
	}
	else if (objectType == MAP_OBJECT_TYPE::HEART ||
		objectType == MAP_OBJECT_TYPE::NUMBER ||
		objectType == MAP_OBJECT_TYPE::ROAD)
	{
		//Character -> 깃발 꼽기 애니메이션 //일하고 있어

		Sprite* flag = Sprite::create(PATH2::FLAG_MARK);
		flag->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		m_pRefSpriteMap->map[x][y]->addChild(flag, 3);

		m_pRefObjectTypeMap->map[x][y] = (MAP_OBJECT_TYPE)
			((int)objectType + (int)MAP_OBJECT_TYPE::FLAG_DELTA);
	}

	return GAME_CODE::NONE;
}

/* Dig */
//음영 타일로 전환
//Dig효과음 + 0.5초 대기

/* 팠는데 하트였다 */
//턴 수 + 2
//하트 개수 + 1
void GameManager::OnHeart()
{
	m_pRefTurnCounter->BonusTurn();
	m_pRefPlanetProgressJar->FindHeart();

	const int x = m_pRefCharPosMap->pos.x;
	const int y = m_pRefCharPosMap->pos.y;
	const auto targetPos = m_pRefSpriteMap->map[x][y]->getPosition();

	Sprite* shade = Sprite::create(m_pRefMapMetaData->tilePath + "_.png");
	shade->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	shade->setPosition(targetPos);
	m_pRefCameraMan->addChild(shade, 4);

	Sprite* star = Sprite::create(PATH2::HEART);
	star->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	star->setPosition(targetPos + Vec2(10, 0));
	m_pRefCameraMan->addChild(star, 5);

	m_pRefObjectTypeMap->map[x][y] = MAP_OBJECT_TYPE::SHADED;
}

/* 팠는데 길이었다. */
void GameManager::OnRoad()
{
	m_pRefTurnCounter->LoseTurn(MAP_OBJECT_TYPE::ROAD);

	const int x = m_pRefCharPosMap->pos.x;
	const int y = m_pRefCharPosMap->pos.y;
	const auto targetPos = m_pRefSpriteMap->map[x][y]->getPosition();

	Sprite* zero = Sprite::create("Tile/0.png");
	zero->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	zero->setPosition(targetPos);
	m_pRefCameraMan->addChild(zero, 4);

	m_pRefObjectTypeMap->map[x][y] = MAP_OBJECT_TYPE::SHADED;
}

/* 팠는데 숫자였다 */
//1. 턴 수 -1
//2. 숫자 보이기
void GameManager::OnNumber()
{
	const int x = m_pRefCharPosMap->pos.x;
	const int y = m_pRefCharPosMap->pos.y;
	const int n = m_pRefNumberDataMap->map[x][y];

	Sprite* shade = Sprite::create(m_pRefMapMetaData->tilePath + "_.png");
	const auto targetPos = m_pRefSpriteMap->map[x][y]->getPosition();
	shade->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	shade->setPosition(targetPos);
	m_pRefCameraMan->addChild(shade, 4);

	Sprite* number = Sprite::create(m_pRefNumberDataMap->paths[n - 1]);
	number->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	number->setPosition(targetPos);
	m_pRefCameraMan->addChild(number, 5);

	m_pRefTurnCounter->LoseTurn(MAP_OBJECT_TYPE::NUMBER);

	m_pRefObjectTypeMap->map[x][y] = MAP_OBJECT_TYPE::SHADED;
}