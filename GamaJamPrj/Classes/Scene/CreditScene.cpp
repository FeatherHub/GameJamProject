#include "Scene/CreditScene.h"

#include "Data\/Constants.h"

#include "SelectScene.h"
#include "CreditScene.h"
#include "Scene\MainScene.h"

Scene* CreditScene::createScene()
{
	auto scene = Scene::create();

	auto layer = CreditScene::create();
	scene->addChild(layer);

	return scene;
}

bool CreditScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	generateSpr();
	generateTouch();
	return true;
}

void CreditScene::generateSpr()
{
	bg = Sprite::create("credit/credit.png");
	bg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

	this->addChild(bg);
}
void CreditScene::generateTouch()
{
	touchToScreen = Sprite::create("credit/touchToScreen.png");
	touchToScreen->setPosition(winSize.width/2, 50);
	this->addChild(touchToScreen);
	touchToScreen->runAction(RepeatForever::create( Sequence::create(FadeOut::create(0.5f), DelayTime::create(0.5f), FadeIn::create(0.5f), nullptr)));

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CreditScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(CreditScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(CreditScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 5);

}

bool  CreditScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	Director::getInstance()->replaceScene(MainScene::createScene());
	return true;
}

void  CreditScene::onTouchMoved(Touch *touch, Event *unused_event)
{

}

void  CreditScene::onTouchEnded(Touch *touch, Event *unused_event)
{


}