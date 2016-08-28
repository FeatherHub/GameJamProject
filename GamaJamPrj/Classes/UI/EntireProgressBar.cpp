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

	m_sprBaseBar = Sprite::create("SelectScene/base.png");
	m_sprBaseBar->setPosition(15, 570);
	m_sprBaseBar->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(m_sprBaseBar);

	m_sprPerBar = Sprite::create("SelectScene/per.png");
	m_sprPerBar->setPosition(15,570);
	m_sprPerBar->setAnchorPoint(Vec2(0, 0.5));
	m_sprPerBar->setScaleX(0);
	this->addChild(m_sprPerBar);


	m_sprPerBar->runAction(Sequence::create(DelayTime::create(0.1f), EaseIn::create( ScaleTo::create(1.0f, 0.2f * guage, 1.0f), 0.5f), nullptr));
}

void EntireProgressBar::generateRose()
{
	// 새싹
	m_sprRose[0] = Sprite::create("SelectScene/bar_seed.png");
	m_sprRose[0]->setAnchorPoint(Vec2(0.5, 0.5));;
	m_sprRose[0]->setPosition(20, 600);
	this->addChild(m_sprRose[0]);

	// 발화?
	m_sprRose[1] = Sprite::create("SelectScene/bar_sprout.png");
	m_sprRose[1]->setAnchorPoint(Vec2(0.5, 0.5));
	m_sprRose[1]->setPosition(200, 600);
	this->addChild(m_sprRose[1]);
	// 장미
	m_sprRose[2] = Sprite::create("SelectScene/bar_rose.png");
	m_sprRose[2]->setAnchorPoint(Vec2(0.5, 0.5));
	m_sprRose[2]->setPosition(320, 600);
	this->addChild(m_sprRose[2]);
}