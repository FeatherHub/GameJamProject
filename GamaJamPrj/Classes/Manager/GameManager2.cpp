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

GAME_CODE GameManager::CharMove()
{
	//Character is in World Space
	const auto& charPos = m_pRefCharacter->getPosition();
	const auto& charDir = m_pRefCharacter->GetDirection();
	const auto& moveDelta = m_pRefDirDeltaPos[(int)charDir];

	bool res =	m_pRefCameraMan->Move(moveDelta);
	if (res == true)
	{
		m_pRefCharPosMap->UpdatePos(charDir);
		return GAME_CODE::NONE;
	}

	//TODO: ������ ��ȿ���� �ʴ� ��Ȳ���� �ִϸ��̼����� ������ ������

	const auto& movedPos = charPos + moveDelta;
	//�� �ٱ����� ����������
	if (movedPos.x >= Constants::VIEWPORT_WIDTH ||
		movedPos.y >= Constants::VIEWPORT_HEIGHT + Constants::VIEWPORT_LEFT_BOTTOM_Y ||
		movedPos.x < 0 || movedPos.y  < Constants::VIEWPORT_LEFT_BOTTOM_Y)
	{
		return GAME_CODE::NONE;
	}
	
	/*
	//���� �浹 �ߴ�
	int charXPos = m_pRefCharPosMap->pos.x;
	int charYPos = m_pRefCharPosMap->pos.y;
	if (m_pRefObjectTypeMap->map[charXPos][charYPos] == MAP_OBJECT_TYPE::WALL)
	{
		return GAME_CODE::NONE;
	}
	*/

	/*
	Note : ĳ������ ��ġ�� ĳ���� �ʿ����� ĳ���� ��ġ�� �����Ѵ�
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
	int charXPos = m_pRefCharPosMap->pos.x;
	int charYPos = m_pRefCharPosMap->pos.y;
	auto objectType = m_pRefObjectTypeMap->map[charXPos][charYPos];

	if (objectType == MAP_OBJECT_TYPE::FLAG_ON_HEART ||
		objectType == MAP_OBJECT_TYPE::FLAG_ON_NUMBER ||
		objectType == MAP_OBJECT_TYPE::FLAG_ON_ROAD)
	{
		//Character -> ��� �̱� �ִϸ��̼� //���ϰ� �־�
		m_pRefObjectTypeMap->map[charXPos][charYPos] = (MAP_OBJECT_TYPE)
			((int)objectType - (int)MAP_OBJECT_TYPE::FLAG_DELTA);
	}
	else if (objectType == MAP_OBJECT_TYPE::HEART ||
		objectType == MAP_OBJECT_TYPE::NUMBER ||
		objectType == MAP_OBJECT_TYPE::ROAD)
	{
		//Character -> ��� �ű� �ִϸ��̼� //���ϰ� �־�
		m_pRefObjectTypeMap->map[charXPos][charYPos] = (MAP_OBJECT_TYPE)
			((int)objectType + (int)MAP_OBJECT_TYPE::FLAG_DELTA);
	}

	return GAME_CODE::NONE;
}

/* Dig */
//���� Ÿ�Ϸ� ��ȯ
//Digȿ���� + 0.5�� ���


/* �ʹµ� ��Ʈ���� */
//�� �� + 2
//��Ʈ ���� + 1
void GameManager::OnHeart()
{
	m_pRefTurnCounter->BonusTurn();
	m_pRefPlanetProgressJar->FindHeart();

	const int x = m_pRefCharPosMap->pos.x;
	const int y = m_pRefCharPosMap->pos.y;

	Sprite* shade = Sprite::create(m_pRefMapMetaData->tilePath + "_.png");
	const auto targetPos = m_pRefSpriteMap->map[x][y]->getPosition();
	shade->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	shade->setPosition(targetPos);
	m_pRefCameraMan->addChild(shade, 3);

	m_pRefObjectTypeMap->map[x][y] = MAP_OBJECT_TYPE::SHADED;
}

/* �ʹµ� ���̾���. */
void GameManager::OnRoad()
{
	m_pRefTurnCounter->LoseTurn(MAP_OBJECT_TYPE::ROAD);
}

/* �ʹµ� ���ڿ��� */
//1. �� �� -1
//2. ���� ���̱�
void GameManager::OnNumber()
{
	const int x = m_pRefCharPosMap->pos.x;
	const int y = m_pRefCharPosMap->pos.y;
	const int n = m_pRefNumberDataMap->map[x][y];

	Sprite* number = Sprite::create(m_pRefNumberDataMap->paths[n]);
	const auto targetPos = m_pRefSpriteMap->map[x][y]->getPosition();
	number->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	number->setPosition(targetPos);
	m_pRefCameraMan->addChild(number, 3);

	m_pRefTurnCounter->LoseTurn(MAP_OBJECT_TYPE::NUMBER);

	m_pRefObjectTypeMap->map[x][y] = MAP_OBJECT_TYPE::SHADED;
}