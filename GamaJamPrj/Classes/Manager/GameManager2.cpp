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
	else if (objectType == MAP_OBJECT_TYPE::HEART ||
		objectType == MAP_OBJECT_TYPE::NUMBER ||
		objectType == MAP_OBJECT_TYPE::ROAD)
	{
		//Character -> 깃발 꼽기 애니메이션 //일하고 있어
		m_pRefObjectTypeMap->map[charXPos][charYPos] = (MAP_OBJECT_TYPE)
			((int)objectType + (int)MAP_OBJECT_TYPE::FLAG_DELTA);
	}

	return GAME_CODE::NONE;
}

/* Dig */

void GameManager::OnHeart()
{
	
}

void GameManager::OnRoad()
{

}

void GameManager::OnNumber()
{

}