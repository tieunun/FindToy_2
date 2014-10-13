#include "BaseToy.h"
#include "ToyPistol.h"
#include "ToyHarmonica.h"
#include "ToyFrog.h"

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
	default:
		break;
	}
	return toy;
}

void BaseToy::onEnter()
{
	BaseNode::onEnter();
	
	_body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING(StringUtils::format("toy_type_%d",_type)));
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
