#pragma once

#include "cocos2d.h"
USING_NS_CC;

class GameScene : public Layer
{
public:
    static Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(Ref* pSender);
    
    CREATE_FUNC(GameScene);
};
