
#include "GameData.h"
#define  STATIC_DATA_PATH "game_data.plist"
	static GameData *instance = NULL;

GameData::GameData(void)
{
}


GameData::~GameData(void)
{
}

GameData *GameData::getInstance()
{
	if (!instance)
	{
		instance = new GameData();
		instance->init();
	}
	return instance;
}

bool GameData::init()
{
	_dic = FileUtils::getInstance()->getValueMapFromFile(STATIC_DATA_PATH);
	//_dic = FileUtils::getInstance()->getva

	return true;
}

void GameData::purge()
{
	CC_SAFE_RELEASE_NULL(instance);
}

const std::string GameData::stringFromKey(const std::string &key)
{
	auto str = _dic[key].asString();
	if (str=="")
	{
		log("plist key of string are null");
	}
	return str;
}

int GameData::intFromKey(const std::string &key)
{
	return _dic[key].asInt();
}

float GameData::floatFromKey(const std::string &key)
{
	return _dic[key].asFloat();
}

bool GameData::booleanFromKey(const std::string &key)
{
	return _dic[key].asBool();
}

Rect GameData::rectFromKey(const std::string &key)
{
	return RectFromString(_dic[key].asString());
}

Size GameData::sizeFromKey(const std::string &key)
{
	return SizeFromString(_dic[key].asString());
}

Vec2 GameData::pointFromKey(const std::string &key)
{
	return PointFromString(_dic[key].asString());
}
