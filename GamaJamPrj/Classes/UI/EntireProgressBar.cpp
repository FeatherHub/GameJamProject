#include "EntireProgressBar.h"
#include "Data\Constants.h"


bool EntireProgressBar::init()
{
	if (!Node::init())
	{
		return false;
	}
	generateBar();
	generateRose();

	return true;
}

void EntireProgressBar :: generateBar()
{
	int guage = 0;
	
	if (UserDefault::getInstance()->getBoolForKey(PATH::STAGE1_BOOL_KEY.c_str()))
		guage++;
	if (UserDefault::getInstance()->getBoolForKey(PATH::STAGE2_BOOL_KEY.c_str()))
		guage++;
	if (UserDefault::getInstance()->getBoolForKey(PATH::STAGE3_BOOL_KEY.c_str()))
		guage++;
	if (UserDefault::getInstance()->getBoolForKey(PATH::STAGE4_BOOL_KEY.c_str()))
		guage++;
	if (UserDefault::getInstance()->getBoolForKey(PATH::STAGE5_BOOL_KEY.c_str()))
		guage++;

	baseBar = Sprite::create("SelectScene/base.png");
	baseBar->setPosition(50, 570);
	baseBar->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(baseBar);

	perBar = Sprite::create("SelectScene/per.png");
	perBar->setPosition(50,570);
	perBar->setAnchorPoint(Vec2(0, 0.5));
	perBar->setScaleX(0);
	this->addChild(perBar);


	perBar->runAction(Sequence::create(DelayTime::create(0.1f), EaseIn::create( ScaleTo::create(1.0f, 0.2f * guage, 1.0f), 0.5f), nullptr));
}

void EntireProgressBar::generateRose()
{
	// 새싹
	rose[0] = Sprite::create("SelectScene/smile.png");
	rose[0]->setAnchorPoint(Vec2(0.5, 0.5));;
	rose[0]->setPosition(50, 600);
	rose[0]->setScale(0.5f);
	this->addChild(rose[0]);

	// 발화?
	rose[1] = Sprite::create("SelectScene/smile.png");
	rose[1]->setAnchorPoint(Vec2(0.5, 0.5));
	rose[1]->setPosition(200, 600);
	rose[1]->setScale(0.5f);
	this->addChild(rose[1]);
	// 장미
	rose[2] = Sprite::create("SelectScene/smile.png");
	rose[2]->setAnchorPoint(Vec2(0.5, 0.5));
	rose[2]->setPosition(300, 600);
	rose[2]->setScale(0.5f);
	this->addChild(rose[2]);
}