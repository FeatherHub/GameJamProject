#pragma once

#include <string>

namespace Constants
{
	const int VIEWPORT_WIDTH_TILE_NUM = 5;
	const int VIEWPORT_HEIGHT_TILE_NUM = 5;

	const float ANI_MOVE_TIME = 1.5f;

	const int TAG_JOYSTICK_TOP = 0;
	const int TAG_JOYSTICK_BOTTOM = 1;
	const int TAG_JOYSTICK_LEFT = 2;
	const int TAG_JOYSTICK_RIGHT = 3;
	const int TAG_JOYSTICK_NUM = 4;
	const int TAG_FLAG_NUM = 5;
	const int TAG_DIG_NUM = 6;

	const int TAG_GOTO_SELECT = 7;
	const int TAG_GOTO_HELP = 8;
	const int TAG_GOTO_CREDIT = 9;

	const std::string DIG_BASE_PATH{ "UI/Dig/dig" };
	const std::string FLAG_BASE_PATH{ "UI/Flag/flag" };
	const std::string JOTSTICK_BASE_PATH{ "UI/JoyStick/joystick" };
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