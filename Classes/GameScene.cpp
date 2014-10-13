
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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("toy_animation_1.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("toy_animation_2.plist");

	//animation
	//pistol
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

	//transformer
	name = GAME_DATA_STRING("toy_transformer_animation");
	
	for ( int i = 0 ;i < 2;i++)
	{
		animation = Animation::create();
		for (int j = 0 ;j < 5 ; j++)
		{
			if (i == 1 && j >1 )
			{
				break;
			}
			auto frame_name = StringUtils::format(name.c_str(),i,j);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frame_name);
			animation->addSpriteFrame(frame);
			
		}

		animation->setDelayPerUnit(.2f);
		
		if ( i == 0)
		{
			animation->setRestoreOriginalFrame(false);
			animation->setLoops(0);
		}
		else
		{
			animation->setRestoreOriginalFrame(true);
			animation->setLoops(10);
		}
		AnimationCache::getInstance()->addAnimation(animation, StringUtils::format("toy_transformer_animation_%d",i));
	}

	//panda
	name = GAME_DATA_STRING("toy_panda_animation_tickle");
	animation = Animation::create();
	for ( int i = 0;i< 2;i++)
	{
		auto frame_name = StringUtils::format(name.c_str(),i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frame_name);
		animation->addSpriteFrame(frame);
	}
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(10);
	animation->setDelayPerUnit(.2f);
	AnimationCache::getInstance()->addAnimation(animation, StringUtils::format("toy_panda_animation_tickle"));
	//cry
	name = GAME_DATA_STRING("toy_panda_animation_cry");
	animation = Animation::create();
	for ( int i = 0;i< 4;i++)
	{
		auto frame_name = StringUtils::format(name.c_str(),i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frame_name);
		animation->addSpriteFrame(frame);
	}
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(10);
	animation->setDelayPerUnit(.2f);
	AnimationCache::getInstance()->addAnimation(animation, StringUtils::format("toy_panda_animation_cry"));

	name = GAME_DATA_STRING("toy_panda_animation_smile");
	animation = Animation::create();
	for ( int i = 0;i< 3;i++)
	{
		auto frame_name = StringUtils::format(name.c_str(),i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frame_name);
		animation->addSpriteFrame(frame);
	}
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(10);
	animation->setDelayPerUnit(.2f);
	AnimationCache::getInstance()->addAnimation(animation, StringUtils::format("toy_panda_animation_smile"));

	name = GAME_DATA_STRING("toy_panda_animation_head_eat");
	animation = Animation::create();
	for ( int i = 0;i< 2;i++)
	{
		auto frame_name = StringUtils::format(name.c_str(),i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frame_name);
		animation->addSpriteFrame(frame);
	}
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(10);
	animation->setDelayPerUnit(.2f);
	AnimationCache::getInstance()->addAnimation(animation, StringUtils::format("toy_panda_animation_head_eat"));

	name = GAME_DATA_STRING("toy_panda_animation_hand_eat");
	
	for ( int i = 0;i< 2;i++)
	{
		animation = Animation::create();
		for (int j = 0;j<2;j++)
		{
			auto frame_name = StringUtils::format(name.c_str(),i,j);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frame_name);
			animation->addSpriteFrame(frame);
		}
		animation->setRestoreOriginalFrame(true);
		if (i == 0)
		{
			animation->setLoops(0);
		}
		else
		{
			animation->setLoops(10);
		}
		animation->setDelayPerUnit(.2f);
		AnimationCache::getInstance()->addAnimation(animation, StringUtils::format("toy_panda_animation_hand_eat_%d",i));
	}

	//frog
	name = GAME_DATA_STRING("toy_frog_animation");
	animation = Animation::create();
	for (int i = 0;i<4;i++)
	{
		auto frame_name = StringUtils::format(name.c_str(),i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frame_name);
		animation->addSpriteFrame(frame);
	}
	animation->setRestoreOriginalFrame(true);
	animation->setDelayPerUnit(.2f);
	animation->setLoops(10);
	AnimationCache::getInstance()->addAnimation(animation, StringUtils::format("toy_frog_animation"));
}


