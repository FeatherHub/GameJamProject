#pragma once

#include "cocos2d.h"
#include "Utils\/Macro.h"

USING_NS_CC;

class CreditScene : public Scene
{
public:
	bool init();
	static Scene* createScene();
	CREATE_FUNC_ARGS(CreditScene);
private:
	void generateTouch();
	void generateSpr();
private:
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
private:
	CREATEWINSIZE;
	Sprite* bg;
	Sprite* touchToScreen;
	EventListenerTouchOneByOne *listener;
};