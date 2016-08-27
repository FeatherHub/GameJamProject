#include "TurnCounter.h"
#include "SimpleAudioEngine.h"
#include "Data/Constants2.h"

bool TurnCounter::init()
{
	if (!Node::init())
	{
		return false;
	}
	generateLabel();

	return true;
}

void TurnCounter::generateLabel()
{
	// 	Label::createWithTTF();
}

void TurnCounter::renewLabel()
{

}

void TurnCounter::BonusTurn()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(PATH2::GOT_BONUS_TURN.c_str());

	curTurn += 2;
}
