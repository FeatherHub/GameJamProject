#include "MapDataLoader.h"

#include "Data/Mapdata.h"

#include <fstream>

MapMetaData* MapDataLoader::GetMapMetaData()
{

	int m_stageNum = UserDefault::getInstance()->getIntegerForKey("NowSelectStage");

	MapMetaData* m_MetaData = new MapMetaData();

	// 경로는 반환값이나 기타 방법으로 받아온다.
	// 인자값으로 m_stageNum 을 넘긴다.
	// TODO : 경로를 반환하는 것 들 등등 만들기?
	std::string path = "test.csv";
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

		m_MetaData->width = user.at("width").asInt();
		m_MetaData->height = user.at("height").asInt();
		m_MetaData->heartNum = user.at("heart\r").asInt();
	}

	switch (m_stageNum)
	{
	case 0:	m_MetaData->tilePath = PATH::METADATA_PATH_1;	break;
	case 1: m_MetaData->tilePath = PATH::METADATA_PATH_2;	break;
	case 2:	m_MetaData->tilePath = PATH::METADATA_PATH_3;	break;
	case 3:	m_MetaData->tilePath = PATH::METADATA_PATH_4;	break;
	case 4:	m_MetaData->tilePath = PATH::METADATA_PATH_5;	break;
	}

	return m_MetaData;
}