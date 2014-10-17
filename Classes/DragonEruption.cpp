#include "DragonEruption.h"

DragonEruption::DragonEruption()
{
	_toyAnimate = false;
}

DragonEruption::~DragonEruption()
{

}

void DragonEruption::onEnter()
{
	BaseNode::onEnter();

	_body = Sprite::create();
	this->setVisible(false);
	this->addChild(_body);
}

void DragonEruption::play()
{
	auto animation = AnimationCache::getInstance()->getAnimation("toy_dragon_animation_eruption");
	_body->runAction(Sequence::create(CallFunc::create([=](){
		_toyAnimate = true;
		this->setVisible(true);
	}),
		Animate::create(animation),
		CallFunc::create([=](){
			_toyAnimate = false;
			this->setVisible(false);
	}),
		NULL
		));
}

void DragonEruption::setEruptionFlipped(bool flipped)
{
	_body->setFlippedX(flipped);
}

