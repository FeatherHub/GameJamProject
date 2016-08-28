#include "MapDataLoader.h"

#include "Data/Mapdata.h"
#include "Data\Constants2.h"

#include <fstream>

MapMetaData* MapDataLoader::GetMapMetaData()
{
	int stageNum = UserDefault::getInstance()->getIntegerForKey(PATH2::NOW_STAGE_KEY.c_str());

	MapMetaData* mapMetaData = new MapMetaData();

	std::string path;

	switch (stageNum)
	{
	case 0: path = PATH::METADATA_PATH_1; break;
	case 1:	path = PATH::METADATA_PATH_2; break;
	case 2:	path = PATH::METADATA_PATH_3; break;
	case 3:	path = PATH::METADATA_PATH_4; break;
	case 4:	path = PATH::METADATA_PATH_5; break;
	}

	std::ifstream file;

	ValueVector users;
	std::string csvStr = FileUtils::getInstance()->getStringFromFile(path);

	ValueVector balls;
	size_t current = 0, found;
	while ((found = csvStr.find_first_of("\n", current)) != std::string::npos){
		balls.push_back(Value(std::string(csvStr, current, found - current)));
		current = found + 1;
	}
	balls.push_back(Value(std::string(csvStr, current, csvStr.size() - current)));

	ValueVector keys;
	current = 0, found;
	while ((found = balls.at(0).asString().find_first_of(",", current)) != std::string::npos){
		keys.push_back(Value(std::string(balls.at(0).asString(), current, found - current)));
		current = found + 1;
	}
	keys.push_back(Value(std::string(balls.at(0).asString(), current, balls.at(0).asString().size() - current)));


	for (int i = 1; i < (int)balls.size(); i++)
	{
		ValueMap userParams;
		ValueVector params;
		current = 0, found;
		while ((found = balls.at(i).asString().find_first_of(",", current)) != std::string::npos){
			params.push_back(Value(std::string(balls.at(i).asString(), current, found - current)));
			current = found + 1;
		}
		params.push_back(Value(std::string(balls.at(i).asString(), current, balls.at(i).asString().size() - current)));



		for (int j = 0; j < (int)params.size(); j++) 
		{
			userParams[keys.at(j).asString()] = params.at(j).asString();
		}
		users.push_back(Value(userParams));
	}


	for (int i = 0; i < (int)users.size() - 1; i++)
	{
		
		ValueMap user = users.at(i).asValueMap();

		mapMetaData->turn = user.at("turn").asInt();
		mapMetaData->width = user.at("width").asInt();
		mapMetaData->height = user.at("height").asInt();
		mapMetaData->heartNum = user.at("heart\r").asInt();
	}

	switch (stageNum)
	{
	case 0:	mapMetaData->tilePath = PATH::STAGE_TILE_PATH_1;	break;
	case 1: mapMetaData->tilePath = PATH::STAGE_TILE_PATH_2;	break;
	case 2:	mapMetaData->tilePath = PATH::STAGE_TILE_PATH_3;	break;
	case 3:	mapMetaData->tilePath = PATH::STAGE_TILE_PATH_4;	break;
	case 4:	mapMetaData->tilePath = PATH::STAGE_TILE_PATH_5;	break;
	}

	return mapMetaData;
}