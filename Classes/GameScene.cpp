
#include "GameScene.h"
#include "GameConfigure.h"

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

    _toyLayer = ToyLayer::create();
    this->addChild(_toyLayer);
    
	return true;
}

void GameScene::preloadResource()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(GAME_RESOURCE_PATH);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_resource_1.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("toy_animation_0.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("toy_animation_1.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("toy_animation_2.plist");
	GameConfigure::getInstance();

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

	this->loadKoalaAnimation();
}

void GameScene::loadKoalaAnimation()
{
    //log(FileUtils::getInstance()->fullPathForFilename("toy_animation_0.png").c_str());
	//front turn left
	auto name = GAME_DATA_STRING("koala_animation_front_turn_left");
	auto animation = Animation::create();
	for (int i = 0;i<2;i++)
	{
		auto frame_name = StringUtils::format(name.c_str(),i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frame_name);
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(.4f);
	animation->setRestoreOriginalFrame(false);
	animation->setLoops(0);
	AnimationCache::getInstance()->addAnimation(animation, StringUtils::format("koala_animation_front_turn_left"));

	//move right
	name = GAME_DATA_STRING("koala_animation_move_right");
	animation = Animation::create();
	for (int i = 0;i<2;i++)
	{
		auto frame_name = StringUtils::format(name.c_str(),i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frame_name);
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(.25f);
	animation->setRestoreOriginalFrame(false);
	animation->setLoops(-1);
	AnimationCache::getInstance()->addAnimation(animation, StringUtils::format("koala_animation_move_right"));

	//right turn back
	name = GAME_DATA_STRING("koala_animation_right_turn_back");
	animation = Animation::create();
	for (int i = 0;i<2;i++)
	{
        auto frame_name = StringUtils::format(name.c_str(),i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frame_name);
        animation->addSpriteFrame(frame);
	}
    auto frame_temp = SpriteFrameCache::getInstance()->getSpriteFrameByName("koala_back_0.png");
    animation->addSpriteFrame(frame_temp);
    //animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("koala_back_0.png"));
	animation->setDelayPerUnit(.4f);
	animation->setRestoreOriginalFrame(false);
	animation->setLoops(0);
	AnimationCache::getInstance()->addAnimation(animation, StringUtils::format("koala_animation_right_turn_back"));

	//up ladder
	name = GAME_DATA_STRING("koala_animation_up_ladder");
	animation = Animation::create();
	for (int i = 1;i<=2;i++)
	{
        auto frame_name = StringUtils::format(name.c_str(),i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frame_name);
        animation->addSpriteFrame(frame);
    }
	animation->setDelayPerUnit(.25f);
	animation->setRestoreOriginalFrame(false);
	animation->setLoops(-1);
	AnimationCache::getInstance()->addAnimation(animation, StringUtils::format("koala_animation_up_ladder"));

	//down ladder with gitf
	name = GAME_DATA_STRING("koala_animation_down_ladder_gift");
	animation = Animation::create();
	for (int i = 0;i<2;i++)
	{
        auto frame_name = StringUtils::format(name.c_str(),i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frame_name);
        animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(.25f);
	animation->setRestoreOriginalFrame(false);
	animation->setLoops(-1);
	AnimationCache::getInstance()->addAnimation(animation, StringUtils::format("koala_animation_down_ladder_gift"));

	//drag ladder
	name = GAME_DATA_STRING("koala_animation_drag_ladder");
    auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
	animation = Animation::create();
	animation->addSpriteFrame(frame);
	animation->setDelayPerUnit(.25f);
	animation->setRestoreOriginalFrame(false);
	animation->setLoops(0);
	AnimationCache::getInstance()->addAnimation(animation, StringUtils::format("koala_animation_drag_ladder"));

	//back
    frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("koala_back_0.png");
	animation = Animation::create();
	animation->addSpriteFrame(frame);
	animation->setDelayPerUnit(.25f);
	animation->setRestoreOriginalFrame(false);
	animation->setLoops(0);
	AnimationCache::getInstance()->addAnimation(animation, StringUtils::format("koala_animation_back"));

	//at ladder
	frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("koala_up_ladder_0.png");
	animation = Animation::create();
	animation->addSpriteFrame(frame);
	animation->setDelayPerUnit(.25f);
	animation->setRestoreOriginalFrame(false);
	animation->setLoops(0);
	AnimationCache::getInstance()->addAnimation(animation, StringUtils::format("koala_animation_at_ladder"));

	//normal
	frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("koala_front_0.png");
	animation = Animation::create();
	animation->addSpriteFrame(frame);
	animation->setDelayPerUnit(.25f);
	animation->setRestoreOriginalFrame(false);
	animation->setLoops(0);
	AnimationCache::getInstance()->addAnimation(animation, StringUtils::format("koala_animation_normal"));

	//smile
	frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("koala_front_0.png");
	animation = Animation::create();
	animation->addSpriteFrame(frame);
	frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("koala_front_1.png");
	animation->addSpriteFrame(frame);
	animation->setDelayPerUnit(1.5f);
	animation->setRestoreOriginalFrame(false);
	animation->setLoops(-1);
	AnimationCache::getInstance()->addAnimation(animation, StringUtils::format("koala_animation_smile"));
}

void GameScene::moveKoala(cocos2d::Vec2 position)
{
    _toyLayer->moveKoala(position);
}


