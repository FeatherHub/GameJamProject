
#include "TurnCounter.h"

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

/*
	����ÿ� �� ����
*/
void TurnCounter::renewLabel()
{

}