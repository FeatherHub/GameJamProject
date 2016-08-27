#include "MovingScene.h"
#include "GameScene.h"

Scene* MovingScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MovingScene::create();
	scene->addChild(layer);

	return scene;
}

bool MovingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	enterGameScene();
	return true;
}

void MovingScene::enterGameScene()
{
	Director::getInstance()->replaceScene(GameScene::createScene());
}