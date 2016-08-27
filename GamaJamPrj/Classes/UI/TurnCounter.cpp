
#include "TurnCounter.h"

bool TurnCounter::init()
{
	if (!Node::init())
	{
		return false;
	}
	generateLabel();

}

void TurnCounter::generateLabel()
{
	// 	Label::createWithTTF();
}

/*
	실행시에 턴 증가
*/
void TurnCounter::renewLabel()
{

}