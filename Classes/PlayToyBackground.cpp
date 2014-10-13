#include "PlayToyBackground.h"
#include "ToyPistol.h"
#include "ToyHarmonica.h"

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
	auto bg = Sprite::createWithSpriteFrameName(bgStr);
	bg->setPosition(_winSize/2);
	this->addChild(bg);
	switch (_type)
	{
	case k_toy_harmonica:
		break;
	default:
		break;
	}

	return true;
}