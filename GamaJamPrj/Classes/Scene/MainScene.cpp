#include "Scene/MainScene.h"
#include "Data\/Constants.h"

#include "SelectScene.h"
#include "CreditScene.h"

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
	generateBg();
	generateMenu();
}

void MainScene::generateBg()
{
	bg = Sprite::create("Texture/MainScene/bg.png");
	bg->setAnchorPoint(Vec2(0.5, 0.5));
	bg->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(bg);
}


void MainScene::generateMenu()
{
	menu = Menu::create();
	this->addChild(menu);

	std::string path = "Texture/MainScene/";

	MenuItem* select = MenuItemImage::create(path + "start.png",path + "start_.png",
		CC_CALLBACK_1(MainScene::callMenu, this));
	select->setTag(Constants::TAG_GOTO_SELECT);
	select->setPosition(0, 100);

	MenuItem* help = MenuItemImage::create(path + "help.png", path + "help_.png", 
		CC_CALLBACK_1(MainScene::callMenu, this));
	help->setTag(Constants::TAG_GOTO_HELP);
	help->setPosition(0, 0);

	MenuItem* credit = MenuItemImage::create(path + "credit.png", path + "credit_.png",
		CC_CALLBACK_1(MainScene::callMenu, this));
	credit->setTag(Constants::TAG_GOTO_CREDIT);
	credit->setPosition(0, -100);

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