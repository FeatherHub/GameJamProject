#include "TurnCounter.h"
#include "SimpleAudioEngine.h"
#include "Data/Constants2.h"

bool TurnCounter::init(int stageTurn)
{
	if (!Node::init())
	{
		return false;

	}
	generateData(stageTurn);
	generateLabel();
	generateShovel();

	return true;
}

void TurnCounter::generateData(int stageTurn)
{
	curTurn = UserDefault::getInstance()->getIntegerForKey(PATH2::TURN_COUNT_KEY.c_str());
	curTurn += stageTurn;
}

void TurnCounter::generateLabel()
{
	std::string str = StringUtils::toString(curTurn);
	label =  Label::createWithTTF(str, "Font/arial.ttf", 50);
	this->addChild(label);
}

void TurnCounter::generateShovel()
{
	shovel = Sprite::create("UI/TurnCounter/shovel.png");
	shovel->setScale(0.4f);
	shovel->setPosition(Vec2(winSize.width/2, 400));
	this->addChild(shovel);
}

void TurnCounter::renewLabel()
{
	std::string str = StringUtils::toString(curTurn);
	label->setString(str);
}

void TurnCounter::LoseTurn(MAP_OBJECT_TYPE mot)
{
	curTurn--;

	switch (mot)
	{
	case MAP_OBJECT_TYPE::ROAD:
		//good sound
		break;
	case MAP_OBJECT_TYPE::NUMBER:
		//normal sound
		break;
	}
}

void TurnCounter::BonusTurn()
{
	
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(PATH2::GOT_BONUS_TURN.c_str());

	curTurn += 2;
}
