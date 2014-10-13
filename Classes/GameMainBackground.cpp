
#include "GameMainBackground.h"


	GameMainBackground::GameMainBackground(void)
{
}


GameMainBackground::~GameMainBackground(void)
{
}

bool GameMainBackground::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	auto bg = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("game_background"));
	bg->setAnchorPoint(Vec2(0,0));

	this->addChild(bg);

	return true;
}


