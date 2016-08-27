#pragma once

#include "cocos2d.h"
#include "Utils\/Macro.h"

USING_NS_CC;

class SelectScene : public Scene
{
public:
	bool init();
	static Scene* createScene();
	CREATE_FUNC_ARGS(SelectScene);
private:
	void generateBg();
private:
	CREATEWINSIZE;
	Sprite* bg;
};