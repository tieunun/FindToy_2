#include "PopToy.h"

PopToy::PopToy()
{
}

PopToy::~PopToy()
{
}

void PopToy::onEnter()
{
	BaseNode::onEnter();
	if (_onEnterCount >1)
	{
		return;
	}
	_body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("toy_holder"));
	this->addChild(_body);
	
	for (int i = 0 ;i < k_toy_count;i++)
	{
		auto toy = BaseToy::create((ToyType)i);
		_toies.pushBack(toy);
	}
}

bool PopToy::isPoped(Vec2 popPos)
{
	for (auto pos :_pops)
	{
		if (pos == popPos)
		{
			return true;
		}
	}
	_pops.push_back(popPos);
	return false;
}

void PopToy::popToy(ToyType type)
{
    this->stopAllActions();
    _body->stopAllActions();
	this->setVisible(true);
    _body->setOpacity(0);
	this->removeChildByTag(105);
		auto delay = DelayTime::create(1);
		this->runAction(Sequence::create(CallFunc::create([=]
		{
			if (type >= 0 && type<k_toy_count)
			{
				auto toy = _toies.at(type);
				this->addChild(toy, 1, 105);
				toy->createFadeOutAction(true);
			}	
			_body->setOpacity(0);
			_body->runAction(FadeIn::create(.5f));
		}
		),
			delay
			,CallFunc::create([=]
		{
			if (type >= 0 && type < k_toy_count)
			{
				auto toy = _toies.at(type);
				toy->createFadeOutAction(false);
			}
			_body->setOpacity(255);
			_body->runAction(FadeOut::create(.5f));
		}
		),CallFunc::create([=]
		{
		}),NULL));
}