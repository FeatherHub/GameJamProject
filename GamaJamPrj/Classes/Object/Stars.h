#pragma once

/*
	2016. 8. 27.
	도인혁 
*/

#include "cocos2d.h"
#include "Utils\/Macro.h"

USING_NS_CC;

// 일단 임의로 정해서 태그값을 넣겠습니다.

class Stars : public Node
{
public:
	bool init(ccMenuCallback func);
	CREATE_FUNC_ARGS(Stars);
	void action();
private:
	void generateStars();

private:
	ccMenuCallback func;
	Menu* stars;
};