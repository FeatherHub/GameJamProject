#include "MapDataLoader.h"

#include "Data/Mapdata.h"

#include <fstream>



bool DataManager::init(int stageNum)
{
	m_stageNum = stageNum;
	loadData();
}

void DataManager::loadData()
{
	// ��δ� ��ȯ���̳� ��Ÿ ������� �޾ƿ´�.
	// ���ڰ����� m_stageNum �� �ѱ��.
	// TODO : ��θ� ��ȯ�ϴ� �� �� ��� �����?
	std::string path =  ""; 
	std::ifstream file;

	ValueVector users;
	std::string csvStr = FileUtils::getInstance()->getStringFromFile(path);
	ValueVector balls = this->split(csvStr, "\n");
	ValueVector keys = this->split(balls.at(0).asString(), ",");
	for (int i = 1; i < (int)balls.size(); i++) {
		ValueMap userParams;
		ValueVector params = this->split(balls.at(i).asString(), ",");
		for (int j = 0; j < (int)params.size(); j++) {
			userParams[keys.at(j).asString()] = params.at(j).asString();
		}
		users.push_back(Value(userParams));
	}


	for (int i = 0; i < (int)users.size(); i++)
	{
		MapMetaData* pMetaData;
		ValueMap user = users.at(i).asValueMap();

		pMetaData->tilePath = user.at("path").asString();
		pMetaData->width = user.at("width").asInt();
		pMetaData->height = user.at("height").asInt();
		pMetaData->heartNum = user.at("heart").asInt();
		pMetaData->tileSize = user.at("size").asInt();
		m_metaData.push_back(pMetaData);
	}
}

	
ValueVector DataManager::split(const std::string &str, const std::string &delim)
{
	ValueVector res;
	size_t current = 0, found;
	while ((found = str.find_first_of(delim, current)) != std::string::npos){
		res.push_back(Value(std::string(str, current, found - current)));
		current = found + 1;
	}
	res.push_back(Value(std::string(str, current, str.size() - current)));
	return res;
}