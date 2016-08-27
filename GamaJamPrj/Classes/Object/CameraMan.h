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
	bool Move(const Vec2& moveDelta);
	bool IsMoving() { return m_isMoving; }
	const Vec2& GetChangedCameraDeltaPos() { return m_ccdp; }
private:
	void InitCameraMapData();
private:
	MapMetaData* m_pRefMapMetaData;
	CameraMapData m_cmd; //camera map data
	Vec2 m_ccdp; //changed camera delta pos
	bool m_isMoving = false;
};