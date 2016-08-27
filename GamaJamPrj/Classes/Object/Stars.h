#pragma once

/*
	2016. 8. 27.
	������ 
*/

#include "cocos2d.h"
#include "Utils\/Macro.h"

USING_NS_CC;

// �ϴ� ���Ƿ� ���ؼ� �±װ��� �ְڽ��ϴ�.

class Stars : public Node
{
public:
	bool init(ccMenuCallback func);
	CREATE_FUNC_ARGS(Stars);
	void action();
private:
	void generateStars();

private:
	ccMenuCallback func;
	Menu* stars;
};