#pragma once

#include <string>

namespace Constants
{
	const int TILE_SIZE = 72;
	const int VIEWPORT_WIDTH_TILE_NUM = 5;
	const int VIEWPORT_HEIGHT_TILE_NUM = 5;
	const int VIEWPORT_WIDTH = VIEWPORT_WIDTH_TILE_NUM * TILE_SIZE;
	const int VIEWPORT_HEIGHT = VIEWPORT_HEIGHT_TILE_NUM * TILE_SIZE;
	const int VIEWPORT_LEFT_BOTTOM_Y = 177;
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

	const int TAG_STAR1 = 10;
	const int TAG_STAR2 = 11;
	const int TAG_STAR3 = 12;
	const int TAG_STAR4 = 13;
	const int TAG_STAR5 = 14;
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

	const std::string STAGE_TILE_PATH_1("Tile/stage1.png");
	const std::string STAGE_TILE_PATH_2("Tile/stage2.png");
	const std::string STAGE_TILE_PATH_3("Tile/stage3.png");
	const std::string STAGE_TILE_PATH_4("Tile/stage4.png");
	const std::string STAGE_TILE_PATH_5("Tile/stage5.png");

	const std::string METADATA_PATH_1("StageInfo/stageInfo1.csv");
	const std::string METADATA_PATH_2("StageInfo/stageInfo2.csv");
	const std::string METADATA_PATH_3("StageInfo/stageInfo3.csv");
	const std::string METADATA_PATH_4("StageInfo/stageInfo4.csv");
	const std::string METADATA_PATH_5("StageInfo/stageInfo5.csv");
}

enum class GAME_CODE : int
{
	NONE,
	WIN,
	LOSE,
};

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