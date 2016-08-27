#include "Stars.h"

#include "Data\Constants.h"

bool Stars::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->func = func;
	generateStars();

	return true;
}

void Stars::generateStars()
{
	stars = Menu::create();
	this->addChild(stars);

	MenuItem* star1 = MenuItemImage::create(PATH::SELECTSCENE_STAR, PATH::SELECTSCENE_STAR, 
		CC_CALLBACK_1(Stars::callStar, this));
	
	star1->setPosition(START_POS_2);
	star1->setTag(POS0);
	star1->setScale(1.0f);
	star1->runAction(RepeatForever::create(Sequence::create( MoveBy::create(1.0f, Vec2(0, 15)), DelayTime::create(0.2f), MoveBy::create(1.0f, Vec2(0, -15)),
		nullptr)));

	
	MenuItem* star2 = MenuItemImage::create(PATH::SELECTSCENE_STAR, PATH::SELECTSCENE_STAR);
	star2->setPosition(START_POS_3);
	star2->setTag(POS1);
	star2->setScale(0.5f);
	star2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.8f, Vec2(0, 5)), DelayTime::create(0.2f), MoveBy::create(0.8f, Vec2(0, -5)),
		nullptr)));

	MenuItem* star3 = MenuItemImage::create(PATH::SELECTSCENE_STAR, PATH::SELECTSCENE_STAR);
	star3->setPosition(START_POS_4);
	star3->setTag(POS2);
	star3->setScale(0.3f);
	star3->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.6f, Vec2(0, 2)), DelayTime::create(0.2f), MoveBy::create(1.6f, Vec2(0, -2)),
		nullptr)));

	MenuItem* star4 = MenuItemImage::create(PATH::SELECTSCENE_STAR, PATH::SELECTSCENE_STAR);
	star4->setPosition(START_POS_5);
	star4->setTag(POS3);
	star4->setScale(0.1f);
	star4->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.6f, Vec2(0, 2)), DelayTime::create(0.2f), MoveBy::create(1.6f, Vec2(0, -2)),
		nullptr)));

	stars->addChild(star1);
	stars->addChild(star2);
	stars->addChild(star3);
	stars->addChild(star4);
}

void Stars::action()
{
	stars->runAction(FadeOut::create(1.0f));
}

void Stars::moveStar()
{

}

void Stars::callStar(Ref* Sender)
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

	// guage 로 현재 선택한 행성에 관련된 값을 알 수 있음
	stars->getChildByTag(POS0)->stopAllActions();
	stars->getChildByTag(POS0)->runAction(Sequence::create(Spawn::create( MoveTo::create(0.5f, START_POS_1), ScaleTo::create(0.5f,1.2f)),
		RepeatForever::create(Sequence::create(MoveBy::create(1.6f, Vec2(0, 2)), DelayTime::create(0.2f), MoveBy::create(1.6f, Vec2(0, -2)),
		nullptr)), nullptr));

	stars->getChildByTag(POS1)->stopAllActions();
	stars->getChildByTag(POS1)->runAction(Sequence::create(Spawn::create(MoveTo::create(0.5f, START_POS_2), ScaleTo::create(0.5f, 1.0f)),
		RepeatForever::create(Sequence::create(MoveBy::create(1.0f, Vec2(0, 15)), DelayTime::create(0.2f), MoveBy::create(1.0f, Vec2(0, -15)),
		nullptr)), nullptr));

	stars->getChildByTag(POS2)->stopAllActions();
	stars->getChildByTag(POS2)->runAction(Sequence::create(Spawn::create(MoveTo::create(0.5f, START_POS_3), ScaleTo::create(0.5f, 0.5f)),
		RepeatForever::create(Sequence::create(MoveBy::create(0.8f, Vec2(0, 5)), DelayTime::create(0.2f), MoveBy::create(0.8f, Vec2(0, -5)),
		nullptr)), nullptr));

	stars->getChildByTag(POS3)->stopAllActions();
	stars->getChildByTag(POS3)->runAction(Sequence::create(Spawn::create(MoveTo::create(0.5f, START_POS_4), ScaleTo::create(0.5f, 0.3f)),
		RepeatForever::create(Sequence::create(MoveBy::create(1.6f, Vec2(0, 2)), DelayTime::create(0.2f), MoveBy::create(1.6f, Vec2(0, -2)),
		nullptr)), nullptr));

	stars->removeFromParent();
}