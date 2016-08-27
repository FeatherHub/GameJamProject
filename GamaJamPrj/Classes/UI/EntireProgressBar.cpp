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
	baseBar->setPosition(50, 50);
	baseBar->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(baseBar);

	perBar = Sprite::create("SelectScene/per.png");
	perBar->setPosition(50, 50);
	perBar->setAnchorPoint(Vec2(0, 0.5));
	perBar->setScaleX(0);
	this->addChild(perBar);


	perBar->runAction(Sequence::create(DelayTime::create(0.1f), EaseIn::create( ScaleTo::create(1.0f, 0.2f * guage, 1.0f), 0.5f), nullptr));
}

void EntireProgressBar::generateRose()
{

}