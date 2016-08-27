#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include "Data/Constants.h"
#include "Data/Mapdata.h"

class CameraMan : public Node
{
public:
	/*
	Note : Call SetMapMetaData and InitCameraMapData !!!
	*/
	CREATE_FUNC(CameraMan);
	virtual bool init() override;
	void SetMapMetaData(MapMetaData* mmd) { m_pRefMapMetaData = mmd; }
	void InitCameraMapData();
	void Move(const Vec2& moveDelta);
private:
	MapMetaData* m_pRefMapMetaData;
	CameraMapData m_cameraMapData;
};