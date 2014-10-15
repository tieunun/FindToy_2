#include "PlayToyBackground.h"
#include "ToyPistol.h"
#include "ToyHarmonica.h"
#include "ClothShelf.h"

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
	default:
		break;
	}

	return true;
}