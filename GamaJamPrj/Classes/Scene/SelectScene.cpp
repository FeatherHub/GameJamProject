#include "Scene/SelectScene.h"
#include "Data\/Constants.h"

#include "SelectScene.h"
#include "CreditScene.h"

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
}

void SelectScene::generateBg()
{

}