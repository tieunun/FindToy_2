#include "ToyTransformer.h"

ToyTransformer::ToyTransformer()
{
	_type = ToyType::k_toy_frog;
	_toyAnimate = false;
}

ToyTransformer::~ToyTransformer()
{

}

void ToyTransformer::onEnter()
{
	BaseNode::onEnter();
	
	_body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("toy_transformer"));
	this->addChild(_body);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ToyTransformer::OnToyTouched,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool ToyTransformer::OnToyTouched(Touch *touch,Event *event)
{
	if (_toyAnimate)
	{
		return true;
	}
	auto location = this->convertTouchToNodeSpace(touch);
	if (_body->getBoundingBox().containsPoint(location))
	{
		_toyAnimate = true;
		this->play();
	}
	return true;
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
	_toyAnimate = false;
}
