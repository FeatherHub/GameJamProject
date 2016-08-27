#include "SelectScene.h"
#include "Data\/Constants.h"
#include "MovingScene.h"
#include "CreditScene.h"
#include "Object/Stars.h"
#include "UI/EntireProgressBar.h"
#include "SimpleAudioEngine.h"

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
	hailo = Sprite::create("MainScene/MainBGHailo.png");
	hailo->setPosition(winSize.width / 2, 0);
	hailo->runAction(RepeatForever::create(
		RotateBy::create(1.0f, 1.5f)));
	this->addChild(hailo);

	bg = Sprite::create("MainScene/MainBG.png");
	bg->setAnchorPoint(Vec2(0.5, 0.5));
	bg->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(bg);

	// 별 초기화
//	star = Sprite::create(PATH::SELECTSCENE_STAR);
//	star->setScale(2.5f);
//	star->setPosition(winSize.width/2, -50);
//	this->addChild(star);
	

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

void SelectScene::closeUp()
{
	stars->action();
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

	//if (guage == 3)	
	Sprout();
	if (guage == 5) Flower();
}

void SelectScene::Sprout()
{
	stars->action();

	runAction(Sequence::create(
		CallFunc::create([&]() { stars->Disable(); }),
		CallFunc::create([&]() {
		bg->runAction(ScaleTo::create(4.3f, 1.24f));
		hailo->runAction(ScaleTo::create(4.3f, 0.8f));
	}),

		DelayTime::create(8.67f),

		CallFunc::create([&]() {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Effect/shot_bub.wav");
	}),

		DelayTime::create(0.1f),

		CallFunc::create([&]() {
		MakeSprout();
	}),

		DelayTime::create(3.67f),

		CallFunc::create([&]() {
		bg->runAction(ScaleTo::create(3.3f, 1.0f));
		hailo->runAction(ScaleTo::create(3.3f, 1.0f));
	}),
		CallFunc::create([&]() { 
		stars->ReverseAction();
		stars->Enable();
	}),
		nullptr
	));
}

void SelectScene::MakeSprout()
{
	sprouty = Sprite::create("SelectScene/bar_sprout.png");
	bg->addChild(sprouty);
	sprouty->setRotation(-40.f);
	sprouty->setPosition(80, 155);
}

void SelectScene::Flower()
{
	stars->action();

	runAction(Sequence::create(
		CallFunc::create([&]() { stars->Disable(); }),
		CallFunc::create([&]() {
		bg->runAction(ScaleTo::create(4.3f, 1.24f));
		hailo->runAction(ScaleTo::create(4.3f, 0.8f));
	}),

		CallFunc::create([&]() {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Effect/gogo_bub.wav");
	}),

		DelayTime::create(7.67f),

		CallFunc::create([&]() {
		MakeFlower();
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Effect/shot_bub.wav");
	}),

		DelayTime::create(5.0f),

		CallFunc::create([&]() {
		Sprite* happyEnd = Sprite::create();
	}),

		DelayTime::create(3.67f),


		nullptr
		));
}

void SelectScene::MakeFlower()
{
	flower = Sprite::create("SelectScene/bar_rose.png");
	bg->addChild(flower);
	flower->setRotation(-40.f);
	flower->setPosition(80, 155);
}
