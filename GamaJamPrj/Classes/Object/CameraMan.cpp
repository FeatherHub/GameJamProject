#include "CameraMan.h"

bool CameraMan::init()
{
	if (Node::init() == false)
	{
		return false;
	}

	setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

	m_isMoving = false;

	return true;
}

void CameraMan::SetMapMetaData(MapMetaData* mmd)
{
	m_pRefMapMetaData = mmd;
	InitCameraMapData();
}

void CameraMan::InitCameraMapData()
{
	/*
	Note : Members mean length
	*/

	int tileSize = Constants::TILE_SIZE;
	int heightTileNum = m_pRefMapMetaData->height;
	int widthTileNum = m_pRefMapMetaData->width;

	m_cmd.mapHeight = tileSize * heightTileNum;
	m_cmd.mapWidth = tileSize * widthTileNum;

	m_cmd.viewHeight = tileSize * Constants::VIEWPORT_HEIGHT_TILE_NUM;
	m_cmd.viewWidth = tileSize * Constants::VIEWPORT_WIDTH_TILE_NUM;

	m_ccdp = Vec2((m_cmd.mapWidth - m_cmd.viewWidth) / 2,
		(m_cmd.mapHeight - m_cmd.viewHeight) / 2);

	//Camera will be set in World Space
	setPosition(Vec2(0 - ((m_cmd.mapWidth - m_cmd.viewWidth) / 2),
		Constants::VIEWPORT_LEFT_BOTTOM_Y - ((m_cmd.mapHeight - m_cmd.viewHeight) / 2)));
}

bool CameraMan::Move(const Vec2& moveDelta)
{
	const auto& movedPos = getPosition() - moveDelta;
	int mapLeft = movedPos.x;
	int mapRight = mapLeft + m_cmd.mapWidth;
	int mapBottom = movedPos.y;
	int mapTop = mapBottom + m_cmd.mapHeight;

	int viewLeft = 0;
	int viewRight = viewLeft + Constants::VIEWPORT_WIDTH;
	int viewBottom = Constants::VIEWPORT_LEFT_BOTTOM_Y;
	int viewTop = viewBottom + Constants::VIEWPORT_HEIGHT;

	if (mapLeft > viewLeft ||
		mapRight < viewRight ||
		mapTop < viewTop ||
		mapBottom > viewBottom)
	{
		return false;
	}
	
	runAction(Sequence::create(
		CallFunc::create([&]() { m_isMoving = true; }),
		MoveBy::create(Constants::ANI_MOVE_TIME, -moveDelta),
		CallFunc::create([&]() { m_isMoving = false; }),
		nullptr));

	return true;
}

