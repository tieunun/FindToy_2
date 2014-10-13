
#include "GameScene.h"

#define GAME_RESOURCE_PATH "game_resource.plist"

	GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

bool GameScene::init()
{
	if (!BaseScene::init())
	{
		return false;
	}
	this->preloadResource();

	_background = GameMainBackground::create();
	this->addChild(_background);

	_staticLayer = GameStaticLayer::create();
	this->addChild(_staticLayer);

	return true;
}

void GameScene::preloadResource()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(GAME_RESOURCE_PATH);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("toy_animation_0.plist");

    auto count = GAME_DATA_INT("toy_cap_pistol_animation_count");
    auto name  = GAME_DATA_STRING("toy_cap_pistol_animation");
    auto animation = Animation::create();
    for(int i = 0;i < count ;i++)
    {
        auto frame_name = StringUtils::format(name.c_str(),i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frame_name);
        animation->addSpriteFrame(frame);
    }
    animation->setDelayPerUnit(.2f);
    animation->setLoops(10);
    animation->setRestoreOriginalFrame(true);
    AnimationCache::getInstance()->addAnimation(animation, "toy_cap_pistol_animation");
}


