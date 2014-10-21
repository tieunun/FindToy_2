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
	toylast->stopAllActions();
	_type = type;

	auto toy = this->getToy();
	toy->setVisible(true);
	SimpleAudioEngine::getInstance()->playEffect("buy_toy_pop.mp3");
	auto actions = Sequence::create(ScaleTo::create(0.0,0.0),
		ScaleTo::create(.2,0.9),ScaleTo::create(.1,.7),
		ScaleTo::create(.1,.8),
		CallFunc::create([=](){

			auto rotate1 = RotateBy::create(.6f,3);
			auto rotate2 = RotateBy::create(1.2f,-6);
			this->runAction(RepeatForever::create(Sequence::create(rotate1,rotate2,rotate1,NULL)));

			auto move1 = MoveBy::create(.6f,Vec2(-10,0));
			auto move2 = MoveBy::create(1.2f,Vec2(20,0));
			this->runAction(RepeatForever::create(Sequence::create(move1,move2,move1,NULL)));
	}),
		NULL);
	toy->runAction(actions);
}

ToyType BuySign::getToyType()
{
    return _type;
}