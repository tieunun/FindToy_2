#include "cocos2d.h"
USING_NS_CC;

class GameConfigure
{
public:
	static GameConfigure *getInstance();
private:
	GameConfigure();
	~GameConfigure();

	void convertStringToVec2();
	void convertVec2ToString();

	std::vector<Vec2> _toyPositions;
	UserDefault *_defaults;
public:

	bool init();
	std::vector<Vec2> changeToyPostion();
	std::vector<Vec2> getToyPosition();
};