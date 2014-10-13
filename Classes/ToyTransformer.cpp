#include "ToyTransformer.h"

ToyTransformer::ToyTransformer()
{
	_type = ToyType::k_toy_frog;
}

ToyTransformer::~ToyTransformer()
{

}

void ToyTransformer::onEnter()
{
	BaseNode::onEnter();
	
	_body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("toy_transformer"));
	this->addChild(_body);
}

void ToyTransformer::play()
{
	auto animation_0 = AnimationCache::getInstance()->getAnimation("toy_transformer_animation_0");
	auto animation_1 = AnimationCache::getInstance()->getAnimation("toy_transformer_animation_1");
	_body->runAction(Sequence::create(Animate::create(animation_0),Animate::create(animation_1),CallFunc::create(this,callfunc_selector(ToyTransformer::onAnimateDone)),NULL));
}

void ToyTransformer::onAnimateDone()
{
	_body->setDisplayFrameWithAnimationName("toy_transformer_animation_0",0);
}
