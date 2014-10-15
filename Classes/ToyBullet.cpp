//
//  ToyBullet.cpp
//  FindToy
//
//  Created by yzl on 14-10-15.
//
//

#include "ToyBullet.h"

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
    
    auto body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("toy_cap_pistol_bullet"));
    this->addChild(body);
    
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
    this->scheduleUpdate();
    
    //this->runAction(MoveBy::create(4, Vec2(-640,0)));
    this->play();
}

void ToyBullet::play()
{

}

bool ToyBullet::OnToyTouched(Touch *touch,Event *event)
{
    return true;
}

void ToyBullet::update(float delta)
{
    static auto lastPos = this->getPosition();
    
    auto angle = Vec2::angle(this->getPosition(), lastPos);
//     ->runAction(RotateTo::create(0, angle));
    this->setRotation(CC_RADIANS_TO_DEGREES(angle));
    lastPos = this->getPosition();
}


