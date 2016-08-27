#pragma once

#include "cocos2d.h"
USING_NS_CC;

class PlanetProgressJar : public Node
{
public:
	CREATE_FUNC(PlanetProgressJar);
	virtual bool init() override;
	void FindHeart() { m_curHeartNum++; }
	int GetHeartNum() { return  m_curHeartNum; }
private:
	int m_curHeartNum;
	int m_objectHeartNum;
};