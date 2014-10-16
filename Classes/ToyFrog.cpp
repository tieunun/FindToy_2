#include "ToyFrog.h"

ToyFrog::ToyFrog()
{
	_type = ToyType::k_toy_frog;
	_toyAnimate = false;
}

ToyFrog::~ToyFrog()
{

}

void ToyFrog::onEnter()
{
	BaseNode::onEnter();

	_body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("toy_frog"));
	this->addChild(_body);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ToyFrog::OnToyTouched,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void ToyFrog::play()
{
	auto animation = AnimationCache::getInstance()->getAnimation("toy_frog_animation");
	_body->runAction(Sequence::create(Animate::create(animation),CallFunc::create([=](){
		_toyAnimate = false;
	}),NULL));
}

bool ToyFrog::OnToyTouched(Touch *touch,Event *event)
{
	if (_toyAnimate)
	{
		return true;
	}
	auto loacation = this->convertTouchToNodeSpace(touch);
	if (_body->getBoundingBox().containsPoint(loacation))
	{
		_toyAnimate = true;
		this->play();
	}
	return true;
}