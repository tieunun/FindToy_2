#include "PlayToyPannelLayer.h"

PlayToyPannelLayer::PlayToyPannelLayer()
{
}

PlayToyPannelLayer::~PlayToyPannelLayer()
{

}

bool PlayToyPannelLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}
	auto back_item1 = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("common_back_btn_nor"));
	auto back_item2 = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("common_back_btn_sel"));
	auto back = MenuItemSprite::create(back_item1,back_item2,CC_CALLBACK_0(PlayToyPannelLayer::onBackButtonClicked,this));
	auto menu = Menu::create(back,NULL);
	menu->setPosition(_winSize.width-50,40);
	this->addChild(menu);
	switch (_type)
	{
	default:
		break;
	}
	return true;
}

PlayToyPannelLayer *PlayToyPannelLayer::create(ToyType type)
{
	auto layer = new PlayToyPannelLayer();
	layer->_type = type;
	layer->init();
	layer->autorelease();
	return layer;
}

void PlayToyPannelLayer::onBackButtonClicked()
{
	Director::getInstance()->popScene();
}