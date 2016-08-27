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

	const std::string AROUND_NUMBER_BASE{ "Tile/" };

}

namespace Constants2
{
	const Vec2 FLAG_POS{ 200,100 };
	const Vec2 DIG_POS{ 150, 50 };
	const Vec2 TURN_COUNTER_POS{ 300, 600 };
	const Vec2 PLANET_PROGRESS_JAR_POS{ 50, 300 };
}
