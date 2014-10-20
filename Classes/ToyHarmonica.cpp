#include "ToyHarmonica.h"
#include "PlayToyBackground.h"
#include "PlayToyScene.h"

ToyHarmonica::ToyHarmonica(void)
{
}


ToyHarmonica::~ToyHarmonica(void)
{
}

void ToyHarmonica::onEnter()
{
	BaseNode::onEnter();
	this->_type = k_toy_harmonica;
	auto body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("toy_harmonica"));
	this->addChild(body);

	Vector<MenuItem*>items(9);
	for (int i = 0 ;i <= 9 ; i++)
	{
		auto temp = std::string(GAME_DATA_STRING("harmonica_num"));
		auto nor = StringUtils::format(temp.c_str(),i);
		//auto keyboardNum = MenuItemImage::create(nor,nor,CC_CALLBACK_1(,this));
		auto nor_sprite = Sprite::createWithSpriteFrameName(nor);
		auto sel_sprite = Sprite::createWithSpriteFrameName(nor);
		sel_sprite->setScale(1.05f);
		auto item = MenuItemSprite::create(nor_sprite,sel_sprite,CC_CALLBACK_1(ToyHarmonica::onHarmonnicaTouched,this));
		item->setTag(1000+i);
		items.pushBack(item);
	}
	auto harmonica_pad = Menu::createWithArray(items);
	harmonica_pad->setPosition(0,-250);
	harmonica_pad->alignItemsHorizontallyWithPadding(10);
	this->addChild(harmonica_pad);
}

void ToyHarmonica::play()
{
	auto scene = PlayToyScene::create(_type);
	Director::getInstance()->pushScene(scene);
}

void ToyHarmonica::onHarmonnicaTouched(Ref *pSender)
{
	auto item = (MenuItemSprite*)pSender;
	auto type = item->getTag() - 1000;
	auto name = StringUtils::format("toy_harmonica_play_%d.mp3",type);

	SimpleAudioEngine::getInstance()->playEffect(name.c_str());
}