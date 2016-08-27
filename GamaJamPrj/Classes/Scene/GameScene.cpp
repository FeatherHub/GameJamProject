#include "GameScene.h"
#include "Manager/GameManager.h"
#include "SimpleAudioEngine.h"
#include "Data\Constants2.h"

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	m_GM = GameManager::create();
	addChild(m_GM);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(PATH2::BG_GAME.c_str(), true);
	scheduleUpdate();



    return true;
}

void GameScene::update(float delta)
{
	auto gmRes = m_GM->update();
	switch (gmRes)
	{
	case GAME_CODE::WIN:
		m_GM->Win();
		break;
	case GAME_CODE::LOSE:
		m_GM->Lose();
		break;
	}
}