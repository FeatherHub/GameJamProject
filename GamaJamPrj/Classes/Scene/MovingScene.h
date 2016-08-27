#pragma once

#include "cocos2d.h"
#include "Utils\/Macro.h"

USING_NS_CC;

class MovingScene : public Scene
{
public:
	static Scene* createScene();
	bool init();
	CREATE_FUNC_ARGS(MovingScene);
private:
	void enterGameScene();
	CREATEWINSIZE;
};