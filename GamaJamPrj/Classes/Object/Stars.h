#pragma once

/*
	2016. 8. 27.
	도인혁 
*/

#include "cocos2d.h"
#include "Utils\/Macro.h"

USING_NS_CC;

// 일단 임의로 정해서 태그값을 넣겠습니다.

#define POS0 0
#define POS1 1
#define POS2 2
#define POS3 3

#define START_POS_1 Vec2 ( - 300, - 200 ) // 화면 밖임
#define START_POS_2 Vec2 ( -100, -90 )	// 가장 크게 보이는 것은 이것
#define START_POS_3 Vec2 ( 40, -10 )
#define START_POS_4 Vec2 ( 150, 10 )
#define START_POS_5 Vec2 ( 200, 40 )

class Stars : public Node
{
public:
	bool init();
	CREATE_FUNC_ARGS(Stars);
	void action();
private:
	void generateStars();
	void moveStar();
	void callStar(Ref* sender);
	void callRenew(Ref* sender);
private:
	CREATEWINSIZE
	ccMenuCallback func;
	Menu* stars;
};

