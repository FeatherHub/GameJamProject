#include "Stars.h"

#include "Data\Constants.h"
#include "Data\Constants2.h"
#include "Scene\MovingScene.h"

bool Stars::init()
{
	if (!Node::init())
	{
		return false;
	}
	generateStars();
	MoveStar();

	return true;
}

void Stars::generateStars()
{
	// 현재 진행 몇 스테이지 인지를 나타냄
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

	m_stars = Menu::create();
	addChild(m_stars);

	std::string path = "SelectScene/" + StringUtils::toString(guage + 1) + "/";

	MenuItem* star1 = MenuItemImage::create(path + "stage1.png", path + "stage1.png",
		CC_CALLBACK_1(Stars::CallStar, this));
	
	star1->setPosition(START_POS_2);
	star1->setTag(POS0);
	star1->setScale(0.3f);
	star1->runAction(RepeatForever::create(Sequence::create( MoveBy::create(1.0f, Vec2(0, 15)), DelayTime::create(0.2f), MoveBy::create(1.0f, Vec2(0, -15)),
		nullptr)));

	
	MenuItem* star2 = MenuItemImage::create(path + "stage2.png", path + "stage2.png");
	star2->setPosition(START_POS_3);
	star2->setTag(POS1);
	star2->setScale(0.15f);
	star2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.8f, Vec2(0, 5)), DelayTime::create(0.2f), MoveBy::create(0.8f, Vec2(0, -5)),
		nullptr)));

	MenuItem* star3 = MenuItemImage::create(path + "stage3.png", path + "stage3.png");
	star3->setPosition(START_POS_4);
	star3->setTag(POS2);
	star3->setScale(0.1f);
	star3->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.6f, Vec2(0, 2)), DelayTime::create(0.2f), MoveBy::create(1.6f, Vec2(0, -2)),
		nullptr)));

	MenuItem* star4 = MenuItemImage::create(path + "stage4.png",  "stage4.png");
	star4->setPosition(START_POS_5);
	star4->setTag(POS3);
	star4->setScale(0.03f);
	star4->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.6f, Vec2(0, 2)), DelayTime::create(0.2f), MoveBy::create(1.6f, Vec2(0, -2)),
		nullptr)));

	m_stars->addChild(star1);
	m_stars->addChild(star2);
	m_stars->addChild(star3);
	m_stars->addChild(star4);
}

void Stars::FadeOut()
{
	m_stars->runAction(FadeOut::create(1.0f));
}

void Stars::FadeIn()
{
	m_stars->runAction(FadeIn::create(1.0f));
}

void Stars::MoveStar()
{
	bool isClear = UserDefault::getInstance()->getBoolForKey(PATH2::IS_CLEAR.c_str());

	if (!isClear)	return;

	UserDefault::getInstance()->setBoolForKey(PATH2::IS_CLEAR.c_str(), false);

	// guage 로 현재 선택한 행성에 관련된 값을 알 수 있음
	m_stars->getChildByTag(POS0)->stopAllActions();
	m_stars->getChildByTag(POS0)->runAction(Sequence::create(DelayTime::create(1.0f), Spawn::create(MoveTo::create(0.5f, START_POS_1), ScaleTo::create(0.5f, 1.2f)),
		RepeatForever::create(Sequence::create(MoveBy::create(1.6f, Vec2(0, 2)), DelayTime::create(0.2f), MoveBy::create(1.6f, Vec2(0, -2)),
		nullptr)), nullptr));

	m_stars->getChildByTag(POS1)->stopAllActions();
	m_stars->getChildByTag(POS1)->runAction(Sequence::create(DelayTime::create(1.0f), Spawn::create(MoveTo::create(0.5f, START_POS_2), ScaleTo::create(0.5f, 1.0f)),
		RepeatForever::create(Sequence::create(MoveBy::create(1.0f, Vec2(0, 15)), DelayTime::create(0.2f), MoveBy::create(1.0f, Vec2(0, -15)),
		nullptr)), nullptr));

	m_stars->getChildByTag(POS2)->stopAllActions();
	m_stars->getChildByTag(POS2)->runAction(Sequence::create(DelayTime::create(1.0f), Spawn::create(MoveTo::create(0.5f, START_POS_3), ScaleTo::create(0.5f, 0.5f)),
		RepeatForever::create(Sequence::create(MoveBy::create(0.8f, Vec2(0, 5)), DelayTime::create(0.2f), MoveBy::create(0.8f, Vec2(0, -5)),
		nullptr)), nullptr));

	m_stars->getChildByTag(POS3)->stopAllActions();
	m_stars->getChildByTag(POS3)->runAction(Sequence::create(DelayTime::create(1.0f), Spawn::create(MoveTo::create(0.5f, START_POS_4), ScaleTo::create(0.5f, 0.3f)),
		RepeatForever::create(Sequence::create(MoveBy::create(1.6f, Vec2(0, 2)), DelayTime::create(0.2f), MoveBy::create(1.6f, Vec2(0, -2)),
		nullptr)), nullptr));

	m_stars->runAction(Sequence::create(DelayTime::create(0.5f), CallFuncN::create(CC_CALLBACK_1(Stars::CallRenew, this)), nullptr));

}

void Stars::CallStar(Ref* Sender)
{
	// 현재 진행 몇 스테이지 인지를 나타냄
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

	UserDefault::getInstance()->setIntegerForKey("NowSelectStage", guage);
	Director::getInstance()->replaceScene(MovingScene::createScene());
}

void Stars::CallRenew(Ref* sender)
{
	m_stars->getChildByTag(POS0)->stopAllActions();
	m_stars->getChildByTag(POS1)->stopAllActions();
	m_stars->getChildByTag(POS2)->stopAllActions();
	m_stars->getChildByTag(POS3)->stopAllActions();
	m_stars->stopAllActions();
	m_stars->removeFromParent();
	generateStars();
}