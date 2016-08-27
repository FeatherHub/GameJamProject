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
	const auto& charPos = m_pRefCharacter->getPosition();
	const auto& charDir = m_pRefCharacter->GetDirection();
	const auto& moveDelta = m_pRefDirDeltaPos[(int)charDir];
	const auto& movedPos = charPos + moveDelta;

	//TODO: ������ ��ȿ���� �ʴ� ��Ȳ���� �ִϸ��̼����� ������ ������

	//�� �ٱ����� ����������
	if (movedPos.x > m_pRefObjectTypeMap->width * Constants::TILE_SIZE ||
		movedPos.y > m_pRefObjectTypeMap->height * Constants::TILE_SIZE ||
		movedPos.x < 0 || movedPos.y < 0)
	{
		return GAME_CODE::NONE;
	}

	//���� �浹 �ߴ�
	int charXPos = m_pRefCharPosMap->pos.x;
	int charYPos = m_pRefCharPosMap->pos.y;
	if (m_pRefObjectTypeMap->map[charXPos][charYPos] == MAP_OBJECT_TYPE::WALL)
	{
		return GAME_CODE::NONE;
	}

	/*
	Note : ĳ������ ��ġ�� ĳ���� �ʿ����� ĳ���� ��ġ�� �����Ѵ�
	*/
	m_pRefCharacter->Move(moveDelta);
	m_pRefCharPosMap->UpdatePos(charDir);

	m_pRefCameraMan->Move(moveDelta);

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
void GameManager::OnRoad()
{

}

void GameManager::OnNumber()
{

}

void GameManager::OnHeart()
{

}
