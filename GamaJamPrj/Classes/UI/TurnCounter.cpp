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
	generatePlnetName();
	generateShovel();

	return true;
}

void TurnCounter::generatePlnetName()
{
	std::string str = StringUtils::toString(m_curTurn);
	int type =		UserDefault::getInstance()->getIntegerForKey(PATH2::NOW_STAGE_KEY.c_str());
	switch (type)
	{
	case 0:	str = "plnet name : K313"; break;
	case 1:	str = "plnet name : J823"; break;
	case 2:	str = "plnet name : D906"; break;
	case 3:	str = "plnet name : G826"; break;
	case 4:	str = "plnet name : F318"; break;
	}

	m_lblPlnet = Label::createWithTTF(str, "Font/arial.ttf", 20);
	m_lblPlnet->setPosition(Vec2(-80, -50));
	this->addChild(m_lblPlnet);
}

void TurnCounter::generateData(int stageTurn)
{
	m_curTurn = UserDefault::getInstance()->getIntegerForKey(PATH2::TURN_COUNT_KEY.c_str());
	m_curTurn += stageTurn;
}

void TurnCounter::generateLabel()
{
	std::string str = StringUtils::toString(m_curTurn);
	m_lblTurn =  Label::createWithTTF(str, "Font/arial.ttf", 30);
	m_lblTurn->setPosition(Vec2(-100, 0));
	this->addChild(m_lblTurn);
}

void TurnCounter::generateShovel()
{
	m_shovelSpr = Sprite::create("UI/TurnCounter/shovel.png");
	m_shovelSpr->setScale(0.25f);
	m_shovelSpr->setPosition(Vec2(-160, 0));
	this->addChild(m_shovelSpr);
}

void TurnCounter::renewLabel()
{
	std::string str = StringUtils::toString(m_curTurn);
	m_lblTurn->setString(str);
}

void TurnCounter::LoseTurn(MAP_OBJECT_TYPE mot)
{
	m_curTurn--;
	renewLabel();
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
}
