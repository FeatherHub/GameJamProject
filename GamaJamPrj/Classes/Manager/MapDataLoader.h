#pragma once

#include "cocos2d.h"
#include "Utils\/Macro.h"

USING_NS_CC;

struct MapMetaData;
class DataManager
{
public:
	bool init(int _stageNum);
	void loadData();
private:	
	std::vector <MapMetaData*> m_metaData;
	int m_stageNum;
	ValueVector split(const std::string &str, const std::string &delim);
};