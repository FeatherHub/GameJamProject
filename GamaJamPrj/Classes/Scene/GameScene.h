#pragma once

#include "cocos2d.h"
USING_NS_CC;

class GameManager;

class GameScene : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);

private:
	void update(float delta);

private:
	GameManager* m_GM;
};
