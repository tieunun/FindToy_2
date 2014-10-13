#include "GameConfigure.h"
#include "GameData.h"
#include "BaseToy.h"

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

	this->convertStringToVec2();

	return true;
}

GameConfigure *GameConfigure::getInstance()
{
	if (!instance)
	{
		instance = new GameConfigure();
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
	std::vector<Vec2> positions;
	while (positions.size()<=k_toy_count)
	{
		auto position = Vec2(int(shelfSize.width *CCRANDOM_0_1()),(int)(shelfSize.height*CCRANDOM_0_1()));
		bool contains = false;
		for (auto temp : positions)
		{
			if (temp == position)
			{
				contains = true;
			}
		}
		if (!contains)
		{
			positions.push_back(position);
		}
	}

	return positions;
}