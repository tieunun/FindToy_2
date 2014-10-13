#include "ToyPistol.h"


ToyPistol::ToyPistol(void)
{
}


ToyPistol::~ToyPistol(void)
{
}

void ToyPistol::onEnter()
{
    BaseNode::onEnter();
	_body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("toy_cap_pistol"));
	this->addChild(_body);
    this->setContentSize(_body->getContentSize());
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan =
        [this](Touch *touch, Event *unusedEvent)->bool
        {
            auto pos = touch->getLocation();
            auto bodyPos = Director::getInstance()->convertToGL(this->_body->getPosition());
            this->play();
            return false;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _body);
    //toy->play();
}

void ToyPistol::play()
{
//    CCSprite *sprite = CCSprite::create("toy_cap_pistol_0.png");
//    this->addChild(sprite,1000);
    auto animation = AnimationCache::getInstance()->getAnimation("toy_cap_pistol_animation");
    
    _body->runAction(Animate::create(animation));
}

