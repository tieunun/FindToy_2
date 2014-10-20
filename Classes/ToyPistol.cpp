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
	_bullet->setVisible(false);
    _bullet->setPosition(0,237);
    
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
	if (_toyAnimate||_bullet->getToyAnimate())
	{
		return false;
	}
	auto location = this->convertTouchToNodeSpace(touch);
	if (fire.containsPoint(location))
	{
		auto effectID = SimpleAudioEngine::getInstance()->playEffect("cap_pistol_fire.mp3",true);
		auto animation = AnimationCache::getInstance()->getAnimation("toy_cap_pistol_animation");
		_body->runAction(Sequence::create(Animate::create(animation),CallFunc::create([=](){
			SimpleAudioEngine::getInstance()->stopEffect(effectID);
			_toyAnimate = false;
		}),NULL));
		_toyAnimate = true;
	}
	return false;
}

void ToyPistol::onBulletBack()
{
	_body->setDisplayFrameWithAnimationName("toy_cap_pistol_animation",0);
}

void ToyPistol::onBulletLanch()
{
	_body->setSpriteFrame("toy_cap_pistol_3.png");
	_bullet->setVisible(true);
}

