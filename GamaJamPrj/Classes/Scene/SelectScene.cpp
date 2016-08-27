#include "SelectScene.h"
#include "Data\/Constants.h"
#include "MovingScene.h"
#include "CreditScene.h"
#include "Object/Stars.h"
#include "UI/EntireProgressBar.h"

Scene* SelectScene::createScene()
{
	auto scene = Scene::create();

	auto layer = SelectScene::create();
	scene->addChild(layer);

	return scene;
}

bool SelectScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	generateBg();
	generateStars();
	generateProBar();
	checkEvent();
	
	//closeUp();
	return true;
}

void SelectScene::generateBg()
{
	// 배경 초기화
	bg = Sprite::create(PATH::SELECTSCENE_BG);
	bg->setAnchorPoint(Vec2(0.5, 0.5));
	bg->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(bg);

	// 별 초기화
	star = Sprite::create(PATH::SELECTSCENE_STAR);
	star->setScale(2.5f);
	star->setPosition(winSize.width/2, -50);
	this->addChild(star);
	
	// 어린 왕자 초기화
	prince = Sprite::create(PATH::SELECTSCENE_PRINCE);
	prince->setPosition(200, 100);
	prince->setScale(0.2f);
	this->addChild(prince);

	// 새싹, 종자, 장미중
	// 스테이지 진행도에 따라서 달라짐
	rose = Sprite::create(PATH::SELECTSCENE_ROSE);
	rose->setPosition(150, 100);
	rose->setScale(0.2f);
	this->addChild(rose);
}

void SelectScene::generateStars()
{
	stars = Stars::create();
	this->addChild(stars);
}
void SelectScene::generateProBar()
{
	bar = EntireProgressBar::create();
	this->addChild(bar);
}

void SelectScene::callStars(Ref* sender)
{
	auto type = (Menu*)sender;

	
}

void SelectScene::closeUp()
{
	stars->action();
	prince->runAction(Sequence::create (Spawn::create( ScaleTo::create(2.5f, 0.8f), MoveBy::create(2.5f, Vec2(0,-50)), nullptr),
		DelayTime::create(0.5f),nullptr));
	star->runAction(Sequence::create(Spawn::create(ScaleTo::create(2.5f, 4.0f), MoveBy::create(2.5f, Vec2(0, -50)), nullptr),
		DelayTime::create(0.5f),  nullptr));
	rose->runAction(Sequence::create(Spawn::create(ScaleTo::create(2.5f, 0.8f), MoveBy::create(2.5f, Vec2(0, -50)), nullptr),
		DelayTime::create(0.5f), nullptr));
	bg->runAction(Sequence::create( DelayTime::create(2.5f), 
		TintTo::create(0.1f, Color3B(0,0, 0)), nullptr));
}

void SelectScene::checkEvent()
{
	int guage = 0;
	if (UserDefault::getInstance()->getBoolForKey(PATH::STAGE1_BOOL_KEY.c_str()))
		guage++;
	if (UserDefault::getInstance()->getBoolForKey(PATH::STAGE2_BOOL_KEY.c_str()))
		guage++;
	if (UserDefault::getInstance()->getBoolForKey(PATH::STAGE3_BOOL_KEY.c_str()))
		guage++;
	if (UserDefault::getInstance()->getBoolForKey(PATH::STAGE4_BOOL_KEY.c_str()))
		guage++;
	if (UserDefault::getInstance()->getBoolForKey(PATH::STAGE5_BOOL_KEY.c_str()))
		guage++;

	if (guage == 3)	Sprout();
	if (guage == 5) Flower();
}

void SelectScene::Sprout()
{

}

void SelectScene::Flower()
{

}
