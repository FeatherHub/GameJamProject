#pragma once

#include "cocos2d.h"
#include "Utils\/Macro.h"

USING_NS_CC;

class Stars;
class EntireProgressBar;
class SelectScene : public Scene
{
public:
	bool init();
	static Scene* createScene();
	CREATE_FUNC_ARGS(SelectScene);
private:
	void generateBg();
	void generateStars();
	void generateProBar();

	void closeUp();
	void callStars(Ref* sender);
private:
	CREATEWINSIZE;
	Sprite* bg;
	Sprite* rose;
	Sprite* prince;
	Sprite* star;
	Stars*	stars;
	EntireProgressBar* bar;
};