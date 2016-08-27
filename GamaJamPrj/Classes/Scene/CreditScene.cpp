#include "Scene/CreditScene.h"

#include "Data\/Constants.h"

#include "SelectScene.h"
#include "CreditScene.h"

Scene* CreditScene::createScene()
{
	auto scene = Scene::create();

	auto layer = CreditScene::create();
	scene->addChild(layer);

	return scene;
}

bool CreditScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	return true;
}