#include "BuySign.h"
#include "BaseToy.h"

BuySign::BuySign()
{
	_type = k_toy_cap_pistol;
}

BuySign::~BuySign()
{

}

bool BuySign::init()
{
	if (!BaseNode::init())
	{
		return false;
	}

	_frame = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("buy_frame"));
	this->addChild(_frame);

	for (int i = 0 ;i<k_toy_count;i++)
	{
		auto toy = Sprite::createWithSpriteFrameName(GAME_DATA_STRING(StringUtils::format("toy_type_%d",i)));
		this->addChild(toy);
		toy->setVisible(false);
		toy->setScale(.7f);
		_toies.pushBack(toy);
	}
	return true;
}

Sprite *BuySign::getToy()
{
	return _toies.at(_type);
}

void BuySign::setToy(ToyType type)
{
	this->setVisible(true);
	auto toylast = _toies.at(_type);
	toylast->setVisible(false);
	_type = type;
	auto toy = this->getToy();
	toy->setVisible(true);
}

ToyType BuySign::getToyType()
{
    return _type;
}