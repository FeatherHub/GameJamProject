#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include "Constants.h"
#include <string>

struct ObjectDataMap
{
	/*
	Format : [x][y]
	*/
	MAP_OBJECT_TYPE** map = nullptr;

	/*
	width x height = tile number
	*/
	int width = -1; 
	int height = -1;
	int tileSize = -1;
};

struct CharacterMapPos
{
	void UpdatePos(DIRECTION dir)
	{
		switch (dir)
		{
		case DIRECTION::UP:
			pos.y++;
			break;
		case DIRECTION::DOWN:
			pos.y--;
			break;
		case DIRECTION::RIGHT:
			pos.x++;
			break;
		case DIRECTION::LEFT:
			pos.x--;
			break;
		}
	}

	Vec2 pos{ -1, -1 };
	int width = -1;
	int height = -1;
};

struct MapMetaData
{
	std::string tilePath;
	int tileSize = -1;
	int heartNum = -1;
	int width = -1;
	int height = -1;
};

struct CameraMapData
{
	/*
	Note : members mean length, not the number of a tile
	*/
	int totalWidth = -1, totalHeight = -1;
	int viewPortWidth = -1, viewPortHeight = -1;
};