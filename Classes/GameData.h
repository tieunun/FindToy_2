
#pragma once
#include "cocos2d.h"
	USING_NS_CC;


#define  GAME_DATA_STRING(key)	GameData::getInstance()->stringFromKey(key)
#define  GAME_DATA_INT(key)		GameData::getInstance()->intFromKey(key)
#define  GAME_DATA_FLOAT(key)		GameData::getInstance()->floatFromKey(key)
#define  GAME_DATA_RECT(key)		GameData::getInstance()->rectFromKey(key)
#define  GAME_DATA_BOOL(key)		GameData::getInstance()->booleanFromKey(key)
#define  GAME_DATA_SIZE(key)		GameData::getInstance()->sizeFromKey(key)
#define  GAME_DATA_POINT(key)		GameData::getInstance()->pointFromKey(key)

class GameData: public Ref
{
public:
	GameData(void);
	~GameData(void);

	static GameData *getInstance();

	bool init();

	void purge();

	const std::string stringFromKey(const std::string &key);
	int intFromKey(const std::string &key);
	float floatFromKey(const std::string &key);
	bool booleanFromKey(const std::string &key);
	Vec2 pointFromKey(const std::string &key);
	Rect rectFromKey(const std::string &key);
	Size sizeFromKey(const std::string &key);


private:
	ValueMap _dic;
};


