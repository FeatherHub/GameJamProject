#pragma once

#include "cocos2d.h"
#include "Utils\/Macro.h"

USING_NS_CC;

class PlanetProgressJar : public Node
{
public:
	CREATE_FUNC_ARGS(PlanetProgressJar);
	bool init(int pAimHeart);
	void FindHeart();
	int GetHeartNum() { return m_curHeart; }
private:
	void generateJar();
	void generateLabel();
private:
	CREATEWINSIZE;
	int m_curHeart;
	int m_aimHeart;
	float m_percent;
	Sprite* m_sprJar;
	Sprite* m_sprLight;
	Label* m_label;

};