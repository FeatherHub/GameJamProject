#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include "ui/UIButton.h"

//UI
class JoyStick;
class Dig;
class Flag;
class TurnCounter;
class PlanetProgressJar;

//Data
struct SpriteMap;
struct NumberDataMap;
struct CharacterPosMap;
struct ObjectTypeMap;
struct MapMetaData;

//Object
class Character;
class CameraMan;

class DataManager : public Node
{
public:
	friend class GameManager;

public:
	CREATE_FUNC(DataManager);
	virtual bool init() override;

private:
	void InitSpriteMap();
	void InitObjectTypeMap();
	void InitNumberDataMap();
	void InitCharPosMap();
	void InitDirDeltaPos();
	void ControllerUICallback(Ref* sender);
private: /* Utility Func */
	bool IsThereHeart(int x, int y);
private:
	//UI
	JoyStick* pJoyStick = nullptr;
	Dig* pBtnDig = nullptr;
	Flag* pBtnFlag = nullptr;
	TurnCounter* pTurnCounter = nullptr;
	PlanetProgressJar* pPlanetProgressJar = nullptr;
	ui::Button* pButton = nullptr;

	//Data
	MapMetaData* pMapMetaData = nullptr;
	SpriteMap* pSpriteMap = nullptr;
	ObjectTypeMap* pObjectTypeMap = nullptr;
	NumberDataMap* pNumberDataMap = nullptr;
	CharacterPosMap* pCharPosMap = nullptr;
	Vec2* pDirDeltaPos = nullptr;

	//Object
	Character* pCharacter = nullptr;
	CameraMan* pCameraMan = nullptr;
};