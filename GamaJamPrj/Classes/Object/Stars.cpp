#include "Stars.h"

#include "Data\Constants.h"

bool Stars::init(ccMenuCallback func)
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

	MenuItem* star1 = MenuItemImage::create(PATH::SELECTSCENE_STAR, PATH::SELECTSCENE_STAR, func);
	star1->setPosition(Vec2(-150, -100));
	star1->setScale(0.8f);
	star1->setTag(Constants::TAG_STAR1);
	stars->addChild(star1);

	MenuItem* star2 = MenuItemImage::create(PATH::SELECTSCENE_STAR, PATH::SELECTSCENE_STAR, func);
	star2->setPosition(Vec2(-50, 125));
	star2->setScale(0.6f);
	star2->setTag(Constants::TAG_STAR2);
	stars->addChild(star2);

	MenuItem* star3 = MenuItemImage::create(PATH::SELECTSCENE_STAR, PATH::SELECTSCENE_STAR, func);
	star3->setPosition(Vec2(150, 0));
	star3->setScale(0.7f);
	star3->setTag(Constants::TAG_STAR3);
	stars->addChild(star3);

	MenuItem* star4 = MenuItemImage::create(PATH::SELECTSCENE_STAR, PATH::SELECTSCENE_STAR, func);
	star4->setPosition(Vec2(0, 200));
	star4->setTag(Constants::TAG_STAR4);
	star4->setScale(0.5f);
	stars->addChild(star4);

	MenuItem* star5 = MenuItemImage::create(PATH::SELECTSCENE_STAR, PATH::SELECTSCENE_STAR, func);
	star5->setPosition(Vec2(100,- 150));
	star5->setScale(0.9f);
	star5->setTag(Constants::TAG_STAR5);
	stars->addChild(star5);


	stars->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.3f, Vec2(0, 10)), DelayTime::create(0.1f), MoveBy::create(0.3f, Vec2(0, -10)),
		nullptr)));
}