#include "Scene/SelectScene.h"
#include "Data\/Constants.h"

#include "SelectScene.h"
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
	// ��� �ʱ�ȭ
	bg = Sprite::create(PATH::SELECTSCENE_BG);
	bg->setAnchorPoint(Vec2(0.5, 0.5));
	bg->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(bg);

	// �� �ʱ�ȭ
	star = Sprite::create(PATH::SELECTSCENE_STAR);
	star->setScale(2.5f);
	star->setPosition(winSize.width/2, -50);
	this->addChild(star);
	
	// � ���� �ʱ�ȭ
	prince = Sprite::create(PATH::SELECTSCENE_PRINCE);
	prince->setPosition(200, 100);
	prince->setScale(0.2f);
	this->addChild(prince);

	// ��� �ʱ�ȭ
	rose = Sprite::create(PATH::SELECTSCENE_ROSE);
	rose->setPosition(150, 100);
	rose->setScale(0.2f);
	this->addChild(rose);
}

void SelectScene::generateStars()
{

}