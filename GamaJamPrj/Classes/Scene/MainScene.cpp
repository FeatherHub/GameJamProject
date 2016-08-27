#include "Scene/MainScene.h"
#include "SelectScene.h"
#include "CreditScene.h"
#include "SimpleAudioEngine.h"

#include "Data\/Constants.h"
#include "Data\Constants2.h"
#include "Manager\MapDataLoader.h"

Scene* MainScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MainScene::create();
	scene->addChild(layer);
	

	return scene;
}

bool MainScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

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

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(PATH2::BG_MAIN.c_str(), true);

	if (guage >= 5)
	{
		hail = Sprite::create("MainScene/MainBGHailo.png");
		hail->setScale(0.75f);
		hail->setPosition(winSize.width / 2, winSize.height / 2);
		hail->runAction(RepeatForever::create(
			RotateBy::create(1.0f, 3.0f)));
		this->addChild(hail);

		Sprite* flower = Sprite::create("SelectScene/bar_rose.png");
		addChild(flower, 6);
		flower->setScale(2.65f);
		flower->setPosition(winSize.width / 2, winSize.height / 2);

		return true;
	}

	generateBg();

	DataSetting();
	generateMenu();

	return true;
}

void MainScene::generateBg()
{
	hail = Sprite::create("MainScene/MainBGHailo.png");
	hail->setPosition(winSize.width / 2, 0);
	hail->runAction(RepeatForever::create(
		RotateBy::create(1.0f, 3.0f)));
	this->addChild(hail);

	bg = Sprite::create("MainScene/MainBG.png");
	bg->setAnchorPoint(Vec2(0.5, 0.5));
	bg->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(bg);
}


void MainScene::generateMenu()
{
	menu = Menu::create();
	this->addChild(menu);

	MenuItem* select = MenuItemImage::create(
		PATH::MAINSCENE_START_BASE + ".png",
		PATH::MAINSCENE_START_BASE + "_.png",
		CC_CALLBACK_1(MainScene::callMenu, this));
	select->setTag(Constants::TAG_GOTO_SELECT);
	select->setPosition(0, 200);

	MenuItem* help = MenuItemImage::create(
		PATH::MAINSCENE_HELP_BASE + ".png", 
		PATH::MAINSCENE_HELP_BASE + "_.png", 
		CC_CALLBACK_1(MainScene::callMenu, this));
	help->setTag(Constants::TAG_GOTO_HELP);
	help->setPosition(0, 100);

	MenuItem* credit = MenuItemImage::create(
		PATH::MAINSCENE_CREDIT_BASE + ".png", 
		PATH::MAINSCENE_CREDIT_BASE + "_.png",
		CC_CALLBACK_1(MainScene::callMenu, this));
	credit->setTag(Constants::TAG_GOTO_CREDIT);
	credit->setPosition(0, 0);

	menu->addChild(select);
	menu->addChild(help);
	menu->addChild(credit);
}

void MainScene::callMenu(Ref* sender)
{
	auto type = (Menu*)sender;
	enterOtherScene(type->getTag());
}

void MainScene::enterOtherScene(int sceneNum)
{
	if (sceneNum == Constants::TAG_GOTO_SELECT)
		Director::getInstance()->replaceScene(SelectScene::createScene());
	else if (sceneNum == Constants::TAG_GOTO_CREDIT)
		Director::getInstance()->replaceScene(CreditScene::createScene());
}

/*
 최초 실행시 데이터 셋팅
*/
void MainScene::DataSetting()
{
	bool isStart = UserDefault::getInstance()->getBoolForKey(PATH2::IS_START.c_str());
	if (!isStart)
	{
		UserDefault::getInstance()->setBoolForKey(PATH2::IS_START.c_str(), true);
		UserDefault::getInstance()->setBoolForKey(PATH2::IS_CLEAR.c_str(), false);

		UserDefault::getInstance()->setIntegerForKey(PATH2::TURN_COUNT_KEY.c_str(), 0);
		UserDefault::getInstance()->setIntegerForKey(PATH2::NOW_STAGE_KEY.c_str(), 0);

		UserDefault::getInstance()->setBoolForKey(PATH::STAGE1_BOOL_KEY.c_str(), false);
		UserDefault::getInstance()->setBoolForKey(PATH::STAGE2_BOOL_KEY.c_str(), false);
		UserDefault::getInstance()->setBoolForKey(PATH::STAGE3_BOOL_KEY.c_str(), false);
		UserDefault::getInstance()->setBoolForKey(PATH::STAGE4_BOOL_KEY.c_str(), false);
		UserDefault::getInstance()->setBoolForKey(PATH::STAGE5_BOOL_KEY.c_str(), false);

	}
		
}