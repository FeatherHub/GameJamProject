#pragma once

#include "cocos2d.h"
#include "Utils\/Macro.h"

USING_NS_CC;

class MainScene : public Scene
{
public:
	bool init();
	static Scene* createScene();
	CREATE_FUNC_ARGS(MainScene);
private:
	void generateBg();
	void generateMenu();

	void callMenu(Ref* sender);
	void enterOtherScene(int sceneNum);
private:
	CREATEWINSIZE;
	Sprite* bg;
	Menu*	menu;
};