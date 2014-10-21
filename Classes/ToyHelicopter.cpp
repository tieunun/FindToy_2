#include "ToyHelicopter.h"
#include "PlayToyPlayLayer.h"

ToyHelicopter::ToyHelicopter()
{
	_type = ToyType::k_toy_frog;
	_toyAnimate = false;
}

ToyHelicopter::~ToyHelicopter()
{

}

void ToyHelicopter::onEnter()
{
	BaseNode::onEnter();

	SimpleAudioEngine::getInstance()->playEffect("toy_helicopter_flying.mp3",true);
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
		auto moveV = this->runAction(MoveBy::create(Max_Down_Height/Toy_Helicopter_Gravity,Vec2(0,-Max_Down_Height)));
		moveV->setTag(103);
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
	SimpleAudioEngine::getInstance()->stopAllEffects();
	SimpleAudioEngine::getInstance()->playEffect("toy_helicopter_boom.mp3");
	_body->stopAllActions();
	this->stopAllActions();
	auto animation = AnimationCache::getInstance()->getAnimation("toy_helicopter_animation_explosion");
	_body->runAction(Sequence::create(Animate::create(animation),CallFunc::create([=](){
		this->setVisible(false);
		SimpleAudioEngine::getInstance()->stopAllEffects();
		auto layer = (PlayToyPlayLayer*)this->getParent();
		layer->showDetailWithSuccess(false);
	}),NULL));
}

//void ToyHelicopter::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
//{
//    if(_toyAnimate)
//    {
//    _customCommand.init(_globalZOrder);
//    _customCommand.func = CC_CALLBACK_0(ToyHelicopter::onDraw, this, transform, flags);
//    renderer->addCommand(&_customCommand);
//    }
//}
//
//void ToyHelicopter::onDraw(const cocos2d::Mat4 &transform, bool transformUpdated)
//{
//    Director* director = Director::getInstance();
//    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
//    glLineWidth( 2.0f );
//    DrawPrimitives::setDrawColor4B(255,0,0,255);
//    
//    DrawPrimitives::drawRect(Vec2(-178,-68),Vec2(-178+174,-68+36));
//    
//    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//}