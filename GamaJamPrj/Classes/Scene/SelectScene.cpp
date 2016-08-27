#include "Scene/SelectScene.h"
#include "Data\/Constants.h"
#include "MovingScene.h"
#include "CreditScene.h"
#include "Object/Stars.h"


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

	// 장미 초기화
	rose = Sprite::create(PATH::SELECTSCENE_ROSE);
	rose->setPosition(150, 100);
	rose->setScale(0.2f);
	this->addChild(rose);
}

void SelectScene::generateStars()
{
	stars = Stars::create(CC_CALLBACK_1(SelectScene::callStars, this));
	this->addChild(stars);
}

void SelectScene::callStars(Ref* sender)
{
	auto type = (Menu*)sender;

	UserDefault::getInstance()->setIntegerForKey("NowSelectStage", type->getTag() - Constants::TAG_STAR1);
	Director::getInstance()->replaceScene(MovingScene::createScene());
}