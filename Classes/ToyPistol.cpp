#include "ToyPistol.h"


ToyPistol::ToyPistol(void)
{
	_toyAnimate = false;
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
    
    _bullet = ToyBullet::create();
    this->addChild(_bullet);
    //_bullet->setPosition(640,360);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(ToyPistol::OnToyTouched,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    //toy->play();
}

void ToyPistol::play()
{

}

bool ToyPistol::OnToyTouched(Touch *touch,Event *event)
{
	static Rect fire = Rect(-22.5,-43,183,144);
	if (_toyAnimate)
	{
		return true;
	}
	auto location = this->convertTouchToNodeSpace(touch);
	if (fire.containsPoint(location))
	{
		auto animation = AnimationCache::getInstance()->getAnimation("toy_cap_pistol_animation");
		_body->runAction(Sequence::create(Animate::create(animation),CallFunc::create([=](){
			_toyAnimate = false;
		}),NULL));
		_toyAnimate = true;
	}
	return true;
}

