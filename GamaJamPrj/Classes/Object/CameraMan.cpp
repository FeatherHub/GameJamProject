#include "CameraMan.h"

bool CameraMan::init()
{
	if (Node::init() == false)
	{
		return false;
	}

	return true;
}

void CameraMan::InitCameraMapData()
{
	/*
	Note : Members mean length
	*/
	/*
	int tileSize = m_pRefMapMetaData->tileSize;
	int heightTileNum = m_pRefMapMetaData->height;
	int widthTileNum = m_pRefMapMetaData->width;

	m_cameraMapData.totalHeight = tileSize * heightTileNum;
	m_cameraMapData.totalWidth = tileSize * widthTileNum;

	m_cameraMapData.viewPortHeight = tileSize * Constants::VIEWPORT_HEIGHT_TILE_NUM;
	m_cameraMapData.viewPortWidth = tileSize * Constants::VIEWPORT_WIDTH_TILE_NUM;
	*/
}

void CameraMan::Move(const Vec2& moveDelta)
{
	const auto& curPos = getPosition();
	int curX = curPos.x;
	int curY = curPos.y;

	const auto& cmd = m_cameraMapData;
	
	if (curX - cmd.viewPortWidth / 2 <= 0 ||
		curX + cmd.viewPortWidth / 2 >= cmd.totalWidth ||
		curY - cmd.viewPortHeight / 2 <= 0 ||
		curY + cmd.viewPortHeight / 2 >= cmd.totalHeight)
	{
		return;
	}

	runAction(MoveBy::create(Constants::ANI_MOVE_TIME, moveDelta));
}

