#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include <array>

struct CharacterMapPos;
struct ObjectDataMap;
class Character;
class CameraMan;
class Dig;
class Flag;
class JoyStick;

class GameManager : public Node
{
public:
	/*
	Note : Call SetMember after create
	*/
	CREATE_FUNC(GameManager);
	virtual bool init() override;
	void update(float delta);

	/*
	ALERT : Must call 6 Set methods
	*/
	void SetCharacter(Character* pCharacter) { m_pRefCharacter = pCharacter; }
	void SetTmxTile(TMXTiledMap* pImageMap) { m_pRefImageMap = pImageMap; }
	void SetObjMapData(ObjectDataMap* pObjMapData) { m_pRefObjectTypeMap = pObjMapData; }
	void SetCharMap(CharacterMapPos* pCharMap) { m_pRefCharMap = pCharMap; }
	void SetDirDeltaPos(Vec2* pDirDeltaPos) { m_pRefdirDeltaPos = pDirDeltaPos; }


private:
	void InitUI();
	void CallUI(Ref* sender);

	void CharMove();
	void CharDig();
	void OnRoad();
	void OnNumber();
	void OnHeart();
	void CharFlag();

private:
	// DataManager 소유 (적절하게 초기화됐다고 가정)
	Character* m_pRefCharacter = nullptr; 
	TMXTiledMap* m_pRefImageMap = nullptr;
	ObjectDataMap* m_pRefObjectTypeMap = nullptr;
	CharacterMapPos* m_pRefCharMap = nullptr;
	Vec2* m_pRefdirDeltaPos = nullptr;
	
	// GameManager 소유
	CameraMan* m_pCameraMan = nullptr;

	// JoyStick, Flag, Dig 등 UI
	JoyStick*	joyStick;
	Dig*		dig;
	Flag*		flag;
};