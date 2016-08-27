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
	generateBg();
	this->scheduleOnce(schedule_selector(MovingScene::enterGameScene), 1.0f);
	return true;
}

void MovingScene::generateBg()
{
	bg = Sprite::create("MovingScene/bg.png");
	bg->setAnchorPoint(Vec2(0.5, 0.5f));
	bg->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(bg);
}

void MovingScene::enterGameScene(float delta)
{
	
	Scene* pscene = GameScene::createScene();
	TransitionScene* tr = TransitionProgressInOut::create(1.0f, pscene);
	
	Director::getInstance()->replaceScene(tr);

}