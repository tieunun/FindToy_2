#include "ToyHelicopter.h"
#include "PlayToyPlayLayer.h"

ToyHelicopter::ToyHelicopter()
{
	_type = ToyType::k_toy_frog;
	_toyAnimate = false;
	_contentRects.push_back(Rect(-178,-68,174,136));
	_contentRects.push_back(Rect(3,4,89,39));
}

ToyHelicopter::~ToyHelicopter()
{

}

void ToyHelicopter::onEnter()
{
	BaseNode::onEnter();

	auto name = GAME_DATA_STRING("toy_helicopter");
	_body = Sprite::createWithSpriteFrameName(name);
	this->addChild(_body);
	_body->setFlippedX(true);
	this->setContentSize(_body->getContentSize());

	auto animation = AnimationCache::getInstance()->getAnimation("toy_helicopter_animation");
	_body->runAction(Animate::create(animation));

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
	listener->onTouchBegan = CC_CALLBACK_2(ToyHelicopter::onHelicopterTouchBegin,this);
	listener->onTouchMoved = CC_CALLBACK_2(ToyHelicopter::onHelicopterTouchMove,this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}

void ToyHelicopter::play()
{

}

bool ToyHelicopter::onHelicopterTouchBegin(Touch *touch,Event *event)
{
	if (!_toyAnimate)
	{
		_toyAnimate = true;
		auto size = Director::getInstance()->getWinSize();
		this->runAction(MoveBy::create(Max_Down_Height/Toy_Helicopter_Gravity,Vec2(0,-Max_Down_Height)));
		auto moveX = size.width/2 - this->getPositionX();
		auto moveH = MoveBy::create(moveX/Toy_Helicopter_H_Speed,Vec2(moveX,0));
		moveH->setTag(101);
		this->runAction(Sequence::create(moveH,CallFunc::create([=](){
			auto layer = (PlayToyPlayLayer*)this->getParent();
			layer->onHelicopterReachCenter();
		}),NULL));
	}
	return true;
}
void ToyHelicopter::onHelicopterTouchMove(Touch *touch,Event *event)
{
	auto lastLocation = touch->getPreviousLocation();
	auto curLocation = touch->getLocation();
	auto move = curLocation.y-lastLocation.y;
	//if (move>0)
	//{
		this->setPosition(this->getPositionX(),this->getPositionY()+move/5);
	//}
	
}

void ToyHelicopter::explode()
{
	_body->stopAllActions();
	this->stopAllActions();
	auto animation = AnimationCache::getInstance()->getAnimation("toy_helicopter_animation_explosion");
	_body->runAction(Sequence::create(Animate::create(animation),CallFunc::create([=](){
		this->setVisible(false);
	}),NULL));
}

std::vector<Rect> ToyHelicopter::getHelicopterContentRects()
{
	return _contentRects; 
}