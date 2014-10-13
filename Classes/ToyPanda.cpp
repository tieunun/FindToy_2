#include "ToyPanda.h"

ToyPanda::ToyPanda()
{
	_type = ToyType::k_toy_frog;
}

ToyPanda::~ToyPanda()
{

}

void ToyPanda::onEnter()
{
	BaseNode::onEnter();

	_body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("toy_panda"));
	this->addChild(_body);
	

	_downPart = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("toy_panda_downPart"));
	_downPart->setVisible(false);
	_downPart->setPosition(0,-94);
	this->addChild(_downPart);

	_head = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("toy_panda_head"));
	_head->setVisible(false);
	_head->setPosition(16,173);
	this->addChild(_head);

	_hand = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("toy_panda_hand"));
	_hand->setVisible(false);
	_hand->setPosition(-18,-9);
	this->addChild(_hand);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ToyPanda::onPandaTouched,this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	_state = k_panda_none;
}

void ToyPanda::play()
{

}

PandaState ToyPanda::getState()
{
	return _state;
}

void ToyPanda::setState(PandaState var)
{
	if (this->_state != var)
	{
		for (auto item :this->getChildren())
		{
			item->stopAllActions();
		}
		this->_state = var;
		switch (var)
		{
		case k_panda_tickle:
			{
			_body->setVisible(true);
			_downPart->setVisible(false);
			_hand->setVisible(false);
			_head->setVisible(false);
			auto animation = AnimationCache::getInstance()->getAnimation("toy_panda_animation_tickle");
			_body->runAction(Sequence::create(Animate::create(animation),CallFunc::create(this,callfunc_selector(ToyPanda::onAnimateDone)),NULL));
			}
			break;
		case  k_panda_cry:
			{
			_body->setVisible(true);
			_downPart->setVisible(false);
			_hand->setVisible(false);
			_head->setVisible(false);
			auto animation = AnimationCache::getInstance()->getAnimation("toy_panda_animation_cry");
			_body->runAction(Sequence::create(Animate::create(animation),CallFunc::create(this,callfunc_selector(ToyPanda::onAnimateDone)),NULL));
			}
			break;
		case k_panda_smile:
			{
			_body->setVisible(true);
			_head->setVisible(true);
			_downPart->setVisible(true);
			_hand->setVisible(false);
			auto animation = AnimationCache::getInstance()->getAnimation("toy_panda_animation_smile");
			_head->runAction(Sequence::create(Animate::create(animation),CallFunc::create(this,callfunc_selector(ToyPanda::onAnimateDone)),NULL));
			}
			break;
		case k_panda_eat:
			{
			_body->setVisible(false);
			_head->setVisible(true);
			_downPart->setVisible(true);
			_hand->setVisible(true);
			auto animation = AnimationCache::getInstance()->getAnimation("toy_panda_animation_head_eat");
			_head->runAction(Sequence::create(Animate::create(animation),CallFunc::create(this,callfunc_selector(ToyPanda::onAnimateDone)),NULL));
			auto animation_0 = AnimationCache::getInstance()->getAnimation("toy_panda_animation_hand_eat_0");
			auto animation_1 = AnimationCache::getInstance()->getAnimation("toy_panda_animation_hand_eat_1");
			_hand->runAction(Sequence::create(Animate::create(animation_0),Animate::create(animation_1),NULL));
			}
		default:
			break;
		}
	}
}

void ToyPanda::onAnimateDone()
{
	_body->setVisible(true);
	_head->setVisible(false);
	_downPart->setVisible(false);
	_hand->setVisible(false);
	_state = k_panda_none;
}

bool ToyPanda::onPandaTouched(Touch *touch,Event *event)
{
	auto touchPos = this->convertTouchToNodeSpace(touch);
	
// 	auto headBox = this->getRectInGL(_head);
// 	auto downBox = this->getRectInGL(_downPart);
// 	auto handBox = this->getRectInGL(_hand);
	auto headBox = _head->getBoundingBox();
	auto downBox = _downPart->getBoundingBox();
	auto handBox = _hand->getBoundingBox();

	if (headBox.containsPoint(touchPos))
	{
		this->setState(k_panda_cry);
	}
	else if (handBox.containsPoint(touchPos))
	{
		this->setState(k_panda_eat);
	}
	else if (downBox.containsPoint(touchPos))
	{
		if (Rect(-260,-300,150,150).containsPoint(touchPos)|| Rect(120,-300,150,150).containsPoint(touchPos))
		{
			this->setState(k_panda_tickle);
		}
		else
		{
			this->setState(k_panda_smile);
		}
	}
	return true;
}