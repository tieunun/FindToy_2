#include "ToyFrog.h"

ToyFrog::ToyFrog()
{
	_type = ToyType::k_toy_frog;
}

ToyFrog::~ToyFrog()
{

}

void ToyFrog::onEnter()
{
	BaseNode::onEnter();

	_body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("toy_frog"));
	this->addChild(_body);
}

void ToyFrog::play()
{
	auto animation = AnimationCache::getInstance()->getAnimation("toy_frog_animation");
	_body->runAction(Animate::create(animation));
}