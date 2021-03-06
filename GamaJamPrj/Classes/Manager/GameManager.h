#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include "Data/Constants.h"

class DataManager;

class JoyStick;
class Dig;
class Flag;
class TurnCounter;
class PlanetProgressJar;

class Character;
class CameraMan; 

struct CharacterPosMap;
struct ObjectTypeMap;
struct NumberDataMap;
struct SpriteMap;
struct MapMetaData;

class GameManager : public Node
{
public:
	/*
	Note : Call SetMember after create
	*/
	CREATE_FUNC(GameManager);
	virtual bool init() override;
	GAME_CODE update();
	void Lose();
	void Win();
private:
	GAME_CODE CharMove();
	GAME_CODE CharDig();
	void OnRoad();
	void OnNumber();
	void OnHeart();
	GAME_CODE CharFlag();

private:
	DataManager* m_pDM = nullptr;
	// DataManager 소유 (적절하게 초기화됐다고 가정)
	JoyStick* m_pRefJoyStick = nullptr;
	Dig* m_pRefBtnDig = nullptr;
	Flag* m_pRefBtnFlag = nullptr;
	TurnCounter* m_pRefTurnCounter = nullptr;
	PlanetProgressJar* m_pRefPlanetProgressJar = nullptr;

	Character* m_pRefCharacter = nullptr;
	CameraMan* m_pRefCameraMan = nullptr;

	SpriteMap* m_pRefSpriteMap = nullptr;
	ObjectTypeMap* m_pRefObjectTypeMap = nullptr;
	CharacterPosMap* m_pRefCharPosMap = nullptr;
	NumberDataMap* m_pRefNumberDataMap = nullptr;
	Vec2* m_pRefDirDeltaPos = nullptr;
	MapMetaData* m_pRefMapMetaData = nullptr;
};