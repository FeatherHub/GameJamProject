#pragma once

namespace Constants
{
	const int VIEWPORT_WIDTH_TILE_NUM = 5;
	const int VIEWPORT_HEIGHT_TILE_NUM = 5;

	const float ANI_MOVE_TIME = 1.5f;
}

enum class CHARACTER_ACTION : int
{
	DIG,
	FLAG,
	MOVE,
	ACTION_NUMBER,
};

enum class DIRECTION : int 
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	DIR_NUM,
	NONE
};
enum class MAP_OBJECT_TYPE : int
{
	ROAD,
	HEART,
	NUMBER,
	FLAG_ON_ROAD,
	FLAG_ON_HEART,
	FLAG_ON_NUMBER,
	WALL,
	FLAG_DELTA = (int)FLAG_ON_ROAD - (int)ROAD,
};