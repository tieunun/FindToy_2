//
//  ToyBullet.cpp
//  FindToy
//
//  Created by yzl on 14-10-15.
//
//

#include "ToyBullet.h"
#include "ToyPistol.h"
#define ToyBullet_Speed 250

ToyBullet::ToyBullet()
{
    _toyAnimate = false;
}
ToyBullet::~ToyBullet()
{
    
}

void ToyBullet::onEnter()
{
    BaseNode::onEnter();
    
    _body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("toy_cap_pistol_bullet"));
    this->addChild(_body);
    
    auto emitter = ParticleSun::create();
    emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("fire.png"));
    this->addChild(emitter);
    emitter->setStartColor(Color4F(1, .2f, .2f, 1));
    emitter->setEndColor(Color4F(1,0,0,1));
        emitter->setGravity(Vec2(300,0));
    emitter->setStartSize(80);
    emitter->setStartSizeVar(20);
    emitter->setEndSize(10);
    emitter->setEndSizeVar(10);
    emitter->setLife(0.4f);
    emitter->setLifeVar(.7f);
//    emitter->setSpeed(300);
    emitter->setPosition(140,0);
    
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ToyBullet::OnToyTouched,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}

void ToyBullet::play()
{
	auto curPos = this->getPosition();
	auto size = Director::getInstance()->getWinSize();
	auto move1 = MoveBy::create((size.width/2 + 200)/ToyBullet_Speed,Vec2(-size.width/2-200,0));
	auto move2 = MoveBy::create((size.width+400)/ToyBullet_Speed,Vec2(size.width+400,0));
	auto move3 = MoveBy::create((size.width/2+200)/ToyBullet_Speed,Vec2(-size.width/2-200,0));
	auto effectID = SimpleAudioEngine::getInstance()->playEffect("cap_pistol_bullet_fire.mp3");
	this->runAction(Sequence::create(CallFunc::create([=](){
		this->setVisible(true);
	}),move1,
		CallFunc::create([=](){
			this->setPosition(this->getPositionX(),-100);
			this->setRotation(180);
	}),
		move2,
		CallFunc::create([=](){
			this->setRotation(0);
			this->setPosition(this->getPositionX(),curPos.y);
	}),
		move3,
		CallFunc::create([=](){
			this->setVisible(false);
			auto pistol = (ToyPistol*)this->getParent();
			pistol->onBulletBack();
			this->_toyAnimate = false;
	}),
		CallFunc::create([=](){
			SimpleAudioEngine::getInstance()->stopEffect(effectID);
	})
		,NULL));

}

bool ToyBullet::OnToyTouched(Touch *touch,Event *event)
{
	auto toy = (ToyPistol*)this->getParent();
	if (_toyAnimate || toy->getToyAnimate())
	{
		return false;
	}
	auto location = this->convertTouchToNodeSpace(touch);
	auto box = _body->getBoundingBox();
	if (_body->getBoundingBox().containsPoint(location))
	{
		_toyAnimate = true;
		this->setVisible(true);
		auto pistol = (ToyPistol*)this->getParent();
		pistol->onBulletLanch();
		this->_toyAnimate = true;
		this->play();
	}
    return false;
}

// void ToyBullet::update(float delta)
// {
//     static auto lastPos = this->getPosition();
//     
//     auto angle = Vec2::angle(this->getPosition(), lastPos);
// //     ->runAction(RotateTo::create(0, angle));
//     this->setRotation(CC_RADIANS_TO_DEGREES(angle));
//     lastPos = this->getPosition();
// }


