#include "GameConfigure.h"
#include "GameData.h"
#include "BaseToy.h"

#define TOY_POSITION "toy_position"
#define TOY_POSITION_DATA_PATH "toy_positions.plist"
static GameConfigure *instance = NULL;
GameConfigure::GameConfigure()
{
	_defaults = NULL;
}

GameConfigure::~GameConfigure()
{
	_defaults->destroyInstance();
}

bool GameConfigure::init()
{
	_toyPositions.clear();
	_defaults = UserDefault::getInstance();
    
    //if(_defaults->getBoolForKey(TOY_POSITION))
    //{
        this->changeToyPostion();
        _defaults->setBoolForKey(TOY_POSITION, true);
        _defaults->flush();
        this->convertVec2ToString();
   // }
	return true;
}

GameConfigure *GameConfigure::getInstance()
{
	if (!instance)
	{
		instance = new GameConfigure();
		instance->init();
	}
	return instance;
}

void GameConfigure::convertStringToVec2()
{
	auto pos = FileUtils::getInstance()->getValueVectorFromFile(TOY_POSITION_DATA_PATH);
	if (pos.size() > 0)
	{
		for (auto temp :pos)
		{
			auto newPos = PointFromString(temp.asString());
			_toyPositions.push_back(newPos);
		}
	}
}

void GameConfigure::convertVec2ToString()
{
	ValueVector values;
	for (auto pos : _toyPositions)
	{
		auto str = StringUtils::format("{%d,%d}",pos.x,pos.y);
		values.push_back(Value(str));
	}
	
	if (values.size())
	{
		ValueMap dic;
		dic.insert(std::map<std::string,Value>::value_type("toy_postions",Value(values)));
		FileUtils::getInstance()->writeToFile(dic,"Resource");
	}
}

std::vector<Vec2> GameConfigure::getToyPosition()
{
	return _toyPositions;
}

std::vector<Vec2> GameConfigure::changeToyPostion()
{
	auto shelfSize = GAME_DATA_SIZE("shelf_size");
	_toyPositions.clear();
	while (_toyPositions.size()<k_toy_count)
	{
		auto position = Vec2((int)(shelfSize.width *CCRANDOM_0_1()),(int)(shelfSize.height*CCRANDOM_0_1()));
		bool contains = false;
		for (auto temp : _toyPositions)
		{
			if (temp == position)
			{
				contains = true;
			}
		}
		if (!contains)
		{
			_toyPositions.push_back(position);
		}
	}
	return _toyPositions;
}