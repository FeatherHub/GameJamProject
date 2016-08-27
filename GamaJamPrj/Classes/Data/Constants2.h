#pragma once

#include <string>


#include "cocos2d.h"
USING_NS_CC;

namespace PATH2
{
	const std::string NOW_STAGE_KEY("NowSelectStage");
	const std::string IS_START("isStart");
	const std::string TURN_COUNT_KEY("TurnCount");
	const std::string IS_CLEAR("isClear");

	const std::string GOT_BONUS_TURN("Sound/Effect/got_bonus_turn.wav");
	const std::string GOT_HEART("Sound/Effect/got_heart.wav");

	const std::string MOVE_EFFECT("Sound/Effect/step.wav ");
	const std::string MARK_EFFECT("Sound/Effect/check.wav  ");
	const std::string DIG_EFFECT("Sound/Effect/dig.wav   ");

	const std::string BG_MAIN("Sound/Bgm/opening.mp3");
	const std::string BG_GAME("Sound/Bgm/ingame.mp3");

	const std::string AROUND_NUMBER_BASE{ "Tile/" };

	const std::string FLAG_MARK{ "Tile/x.png" };

	const std::string HEART{ "Tile/star.png" };
}

namespace Constants2
{
	const Vec2 FLAG_POS{ 200,100 };
	const Vec2 DIG_POS{ 150, 50 };
	const Vec2 TURN_COUNTER_POS{ 300, 600 };
	const Vec2 PLANET_PROGRESS_JAR_POS{ 50, 300 };
}
