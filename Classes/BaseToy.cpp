#include "BaseToy.h"
#include "ToyPistol.h"
#include "ToyHarmonica.h"
#include "ToyFrog.h"
#include "PlayToyScene.h"
#include "ToyTransformer.h"
#include "ToyDoll.h"
#include "ToyPanda.h"
#include "ToyHelicopter.h"

BaseToy::BaseToy(void)
{
}


BaseToy::~BaseToy(void)
{
}

BaseToy *BaseToy::create(ToyType type)
{
	auto toy = new BaseToy();
	toy->init();
	toy->autorelease();

	toy->_type = type;
	if (type < 0 || type > k_toy_count)
	{
		toy->_type = k_toy_cap_pistol;
	}
	return toy;
}

BaseToy *BaseToy::createBig(ToyType type)
{
	BaseToy *toy = NULL;
	switch (type)
	{
	case k_toy_cap_pistol:
		toy = ToyPistol::create();
		break;
	case k_toy_harmonica:
		toy = ToyHarmonica::create();
		break;
	case  k_toy_transformer:
		toy = ToyTransformer::create();
		break;
	case k_toy_frog:
		toy = ToyFrog::create();
		break;
	case k_toy_panda:
		toy = ToyPanda::create();
		break;
	case k_toy_doll:
		toy = ToyDoll::create();
		break;
	case k_toy_helicopter:
		toy = ToyHelicopter::create();
	default:
		break;
	}
	return toy;
}

void BaseToy::onEnter()
{
	BaseNode::onEnter();
	
	_body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING(StringUtils::format("toy_type_%d",_type)));

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(BaseToy::OnToyTouched,this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	this->addChild(_body);
}

void BaseToy::play()
{
	switch (_type)
	{
	case k_toy_cap_pistol:
		break;
	default:
		break;
	}
}

bool BaseToy::OnToyTouched(Touch *touch,Event *event)
{
	if (!this->isVisible())
	{
		return false;
	}
	auto location = this->convertTouchToNodeSpace(touch);
	if (_body->getBoundingBox().containsPoint(location))
	{
		auto secen = PlayToyScene::create(_type);
		Director::getInstance()->pushScene(secen);
	}
	return false;
}

Rect BaseToy::getBox()
{
	static auto offset = 10;
	auto size = _body->getContentSize();
	return Rect(this->getPositionX()-size.width/2+offset,this->getPositionY()-size.height/2+offset,size.width-offset,size.height-offset);
}
