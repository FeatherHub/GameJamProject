#pragma once

#include "cocos2d.h"
#include "Utils\/Macro.h"

USING_NS_CC;

class PlanetProgressJar : public Node
{
public:
	CREATE_FUNC_ARGS(PlanetProgressJar);
	virtual bool init() override;
	void FindHeart() { m_curHeart++; }
	int GetHeartNum() { return m_curHeart; }

private:
	int m_curHeart;


};