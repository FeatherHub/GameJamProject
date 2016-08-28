#pragma once

#include "cocos2d.h"
#include "Utils/Macro.h"

USING_NS_CC;

class EntireProgressBar : public Node
{
public :
	bool init();
	CREATE_FUNC_ARGS(EntireProgressBar);
private:
	void generateBar();
	void generateRose();

private:
	CREATEWINSIZE;
	Sprite* m_sprBaseBar;
	Sprite* m_sprPerBar;
	Sprite* m_sprRose[3];
};

