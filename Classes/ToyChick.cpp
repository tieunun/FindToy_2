#include "ToyChick.h"
#define Toy_Chick_Speed 200

ToyChick::ToyChick()
{
	_type = ToyType::k_toy_frog;
}

ToyChick::~ToyChick()
{

}

void ToyChick::onEnter()
{
	BaseNode::onEnter();

	SimpleAudioEngine::getInstance()->playEffect("toy_chick_water.mp3",true);
	_body = Sprite::create();
	_body->setAnchorPoint(Vec2(.5f,.1f));
	this->addChild(_body);
	this->play();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ToyChick::onChickTouched,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}

void ToyChick::play()
{
	auto animation = AnimationCache::getInstance()->getAnimation("toy_chick_animation");
	_body->runAction(Animate::create(animation));
}

bool ToyChick::onChickTouched(Touch *touch,Event *event)
{
	static Rect rect = Rect(12,135,1125,105);

	auto location1 = this->getParent()->convertTouchToNodeSpace(touch);
	auto location2 = this->convertTouchToNodeSpace(touch);
	if (rect.containsPoint(location1))
	{
		this->stopActionByTag(104);
		_body->setFlippedX(location2.x>0?true:false);
		auto move = MoveBy::create(location2.distance(Vec2(0,0))/Toy_Chick_Speed,location2);
		move->setTag(104);
		this->runAction(move);
		SimpleAudioEngine::getInstance()->playEffect("toy_chick_quack.mp3");
	}
	return true;
}