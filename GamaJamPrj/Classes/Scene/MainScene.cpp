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
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic( PATH2::BG_MAIN.c_str(), true);

	return scene;
}

bool MainScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	DataSetting();
	generateBg();
	generateMenu();


	return true;
}

void MainScene::generateBg()
{
	bg = Sprite::create(PATH::MAINSCENE_BG);
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