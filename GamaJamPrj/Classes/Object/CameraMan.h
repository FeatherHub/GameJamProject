#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include "Data/Constants.h"
#include "Data/Mapdata.h"

class CameraMan : public Node
{
public:
	CREATE_FUNC(CameraMan);
	virtual bool init() override;
	void SetMapMetaData(MapMetaData* mmd);
	void Move(const Vec2& moveDelta);
private:
	void InitCameraMapData();
private:
	MapMetaData* m_pRefMapMetaData;
	CameraMapData m_cameraMapData;
};