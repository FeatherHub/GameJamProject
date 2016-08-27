#pragma once

#include <string>

namespace Constants
{
	const int TILE_SIZE = 72;
	const int VIEWPORT_WIDTH_TILE_NUM = 5;
	const int VIEWPORT_HEIGHT_TILE_NUM = 5;

	const float ANI_MOVE_TIME = 1.5f;

	const int TAG_JOYSTICK_TOP = 0;
	const int TAG_JOYSTICK_BOTTOM = 1;
	const int TAG_JOYSTICK_LEFT = 2;
	const int TAG_JOYSTICK_RIGHT = 3;
	const int TAG_JOYSTICK_NUM = 4;
	const int TAG_FLAG = 5;
	const int TAG_DIG = 6;

	const int TAG_GOTO_SELECT = 7;
	const int TAG_GOTO_HELP = 8;
	const int TAG_GOTO_CREDIT = 9;
}

namespace PATH
{
	const std::string MAINSCENE_BG{ "MainScene/bg.png" };
	const std::string MAINSCENE_START_BASE{ "MainScene/start" };
	const std::string MAINSCENE_CREDIT_BASE{ "MainScene/credit" };
	const std::string MAINSCENE_HELP_BASE{ "MainScene/help" };

	const std::string DIG_BASE{ "UI/Dig/dig" };
	const std::string FLAG_BASE{ "UI/Flag/flag" };
	const std::string JOTSTICK_BASE{ "UI/JoyStick/joystick" };

	const std::string SELECTSCENE_BG("SelectScene/bg.png");
	const std::string SELECTSCENE_STAR("SelectScene/star.png");
	const std::string SELECTSCENE_ROSE("SelectScene/rose.png");
	const std::string SELECTSCENE_PRINCE("SelectScene/prince.png");
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