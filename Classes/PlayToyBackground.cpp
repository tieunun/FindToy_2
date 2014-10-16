#include "PlayToyBackground.h"
#include "ToyPistol.h"
#include "ToyHarmonica.h"
#include "ClothShelf.h"
#include "ToyHelicopter.h"
#include "PlayToyScene.h"

PlayToyBackground::PlayToyBackground()
{

}

PlayToyBackground::~PlayToyBackground()
{

}

PlayToyBackground *PlayToyBackground::create(ToyType toyType)
{
	auto layer = new PlayToyBackground();
	layer->_type = toyType;
	layer->init();
	layer->autorelease();
	return layer;
}

bool PlayToyBackground::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	auto bgName = GAME_DATA_STRING("toy_background_type");
	auto bgStr  = StringUtils::format(bgName.c_str(),_type);
	auto bg_frame_name = GAME_DATA_STRING(bgStr);
	auto bg = Sprite::createWithSpriteFrameName(bg_frame_name);
	bg->setPosition(_winSize/2);
	this->addChild(bg);
	switch (_type)
	{
	case k_toy_harmonica:
		break;
	case k_toy_doll:
		{
			auto clothShelf = ClothShelf::create();
			clothShelf->setPosition(-322,-29);
			this->addChild(clothShelf);
		}
		break;
	case k_toy_helicopter:
		{
			this->removeAllChildren();
			auto bg1 = Sprite::create("toy_background_6.jpg");
			bg1->setAnchorPoint(Vec2(0,0));
			this->addChild(bg1,0,11);
			auto bg2 = Sprite::create("toy_helicopter_grass.png");
			bg2->setAnchorPoint(Vec2(0,0));
			this->addChild(bg2);
			auto bg3 = Sprite::create("toy_helicopter_block_0.png");
			bg3->setAnchorPoint(Vec2(0,0));
			this->addChild(bg3);
			auto bg4 = Sprite::create("toy_helicopter_block_1.png");
			bg4->setPosition(1709,559);
			this->addChild(bg4);
			
		}
		break;
	default:
		break;
	}

	return true;
}

void PlayToyBackground::move()
{
	auto bg = this->getChildByTag(11);
	auto size = bg->getContentSize();
	auto moveH = MoveBy::create((size.width-_winSize.width)/Toy_Helicopter_H_Speed,Vec2(-(size.width-_winSize.width),0));
	moveH ->setTag(11);
	this->runAction(Sequence::create(moveH,CallFunc::create([=](){
		auto scene = (PlayToyScene*)this->getParent();
		scene->moveHelicopter();
	}),NULL));
}