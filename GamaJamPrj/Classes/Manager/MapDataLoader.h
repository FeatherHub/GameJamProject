#pragma once

#include "cocos2d.h"
#include "Utils\/Macro.h"

USING_NS_CC;

struct MapMetaData;

class MapDataLoader
{
public:
	static MapMetaData* GetMapMetaData();
};