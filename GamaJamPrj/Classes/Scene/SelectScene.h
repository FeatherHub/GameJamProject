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

	void Sprout();
	void MakeSprout();
	Sprite* sprouty;

	void Flower();
	void MakeFlower();
	Sprite* flower;


	void checkEvent();
	void closeUp();
private:
	CREATEWINSIZE;
	Sprite* bg;
	Sprite* hailo;
	Sprite* rose;
	Sprite* prince;
	Stars*	stars;
	EntireProgressBar* bar;
};