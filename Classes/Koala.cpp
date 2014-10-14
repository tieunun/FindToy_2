#include "Koala.h"
#define Koala_Speed 100.0f

Koala::Koala()
{
    _lastPosition = Vec2(0,0);
    _targetPosition = Vec2(0,0);
    _originPosition = Vec2(0,0);
    _isKoalaAimate = false;
    _state = k_koala_normal;
}

Koala::~Koala()
{

}

void Koala::onEnter()
{
	BaseNode::onEnter();

	_body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("koala"));
	this->addChild(_body);

//	auto listener = EventListenerTouchOneByOne::create();
//	listener->setSwallowTouches(true);
//	listener->onTouchBegan = [=](Touch *touch,Event *event)->bool
//	{
//		_body->runAction(this->getActionForState(k_koala_front_turn_right));
//		return true;
//	};
//
//	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}

void Koala::setState(const KoalaState state)
{
	_state = state;
}

KoalaState Koala::getState() const
{
	return _state;
}

FiniteTimeAction *Koala::getActionForState(const KoalaState state)
{
	Animation *animation = NULL;
	auto movePos = Vec2(_targetPosition.x-_lastPosition.x,-_originPosition.y+_targetPosition.y);
	auto durationX = abs(movePos.x) / Koala_Speed;
	auto durationY = abs(movePos.y)/Koala_Speed;
	switch (state)
	{
	case  k_koala_up_ladder:
	case k_koala_down_ladder:
		{
			animation = AnimationCache::getInstance()->getAnimation("koala_animation_up_ladder");
            auto animate = Animate::create(animation);
            return Sequence::create(Spawn::create(this->getCallAction(state),MoveBy::create(durationY,Vec2(0,movePos.y)),CallFunc::create([&](){
                //_body->stopAllActions();
                _body->runAction(animate);
            }),NULL),
				this->getActionForState(k_koala_back),
				
                                    CallFunc::create([=](){
                _body->stopAction(animate);
            }), NULL);
		}
		break;
	case k_koala_down_with_gift:
		{
			animation = AnimationCache::getInstance()->getAnimation("koala_down_ladder_gift");
		}
	case  k_koala_drag_ladder_move:
		{
			animation = AnimationCache::getInstance()->getAnimation("koala_animtion_drag_ladder");
			auto animation1 = AnimationCache::getInstance()->getAnimation("koala_animation_up_ladder");
			auto animate = _body->runAction(Sequence::create(Animate::create(animation),Animate::create(animation1),NULL));
			auto move = MoveBy::create(durationX,Vec2(movePos.x,0));
			return Sequence::create(Spawn::create(this->getCallAction(state),move,NULL),this->getActionForState(k_koala_back),NULL);
		}
		break;
	case  k_koala_move_left:
	case  k_koala_move_right:
		{
			animation = AnimationCache::getInstance()->getAnimation("koala_animation_move_right");
            
            auto internelState = movePos.x<0?k_koala_move_left:k_koala_move_right;
			if (internelState == k_koala_move_right)
			{
				_body->setFlippedX(false);
			}
			else
			{
				_body->setFlippedX(true);
			}
            auto animate = Animate::create(animation);
            animate->setTag(state);

//			_body ->runAction(Animate::create(animation));
			auto moveH = MoveBy::create(durationX,Vec2(movePos.x,0));
            return Sequence::create( Spawn::create(CallFunc::create([=](){
                _body->runAction(animate);
            }),moveH,this->getCallAction(internelState),NULL),CallFunc::create([=](){
                _body->stopActionByTag(state);
                }),NULL);
		}
		break;
	case k_koala_front_turn_left:
		{
			_body->setFlippedX(false);
			animation = AnimationCache::getInstance()->getAnimation("koala_animation_front_turn_left");
			return Sequence::create(Spawn::create(Animate::create(animation),this->getCallAction(state),NULL),NULL);
		}
		break;
	case  k_koala_front_turn_right:
		{
			_body->setFlippedX(true);
			animation = AnimationCache::getInstance()->getAnimation("koala_animation_front_turn_left");
			return Sequence::create(Spawn::create(Animate::create(animation),this->getCallAction(state),NULL),NULL);
		}
		break;
	case k_koala_back_turn_left:
		_body->setFlippedX(true);
		animation = AnimationCache::getInstance()->getAnimation("koala_animation_right_turn_back");
		return Animate::create(animation);/* Sequence::create(Spawn::create(Animate::create(animation),this->getCallAction(state),NULL),NULL);*/
		break;
	case k_koala_back_turn_right:
		_body->setFlippedX(false);
		animation = AnimationCache::getInstance()->getAnimation("koala_animation_right_turn_back");
		return Spawn::create(Animate::create(animation)->reverse(),this->getCallAction(state),NULL);
		break;
	case k_koala_left_turn_back:
		_body->setFlippedX(true);
		animation = AnimationCache::getInstance()->getAnimation("koala_animation_right_turn_back");
		return Spawn::create(Animate::create(animation)->reverse(),this->getCallAction(state),NULL);
		break;
	case k_koala_left_turn_front:
		_body->setFlippedX(true);
		animation = AnimationCache::getInstance()->getAnimation("koala_animation_front_turn_left");
		return Spawn::create(Animate::create(animation),this->getCallAction(state),NULL);
		break;
	case k_koala_right_turn_front:
		animation = AnimationCache::getInstance()->getAnimation("koala_animation_front_turn_left");
		return Spawn::create(Animate::create(animation)->reverse(),this->getCallAction(state),NULL);
		break;
	case k_koala_right_turn_back:
		animation = AnimationCache::getInstance()->getAnimation("koala_animation_right_turn_back");
		return Spawn::create(Animate::create(animation),this->getCallAction(state),NULL);
		break;
	case  k_koala_back:
		animation = AnimationCache::getInstance()->getAnimation("koala_animation_back");
		return Sequence::create(CallFunc::create([=](){
			//_body->stopAllActions();
		}),Spawn::create(Animate::create(animation),CallFunc::create([=](){
			_state = state;
		}),NULL),NULL);
	default:
		break;
	}
	return Spawn::createWithTwoActions(Animate::create(animation),(FiniteTimeAction*)this->getCallAction(state));
}

FiniteTimeAction *Koala::getCallAction(KoalaState state)
{
	return CallFunc::create([=]()
	{
		this->_state = state;
	}
	);
}

void Koala::move(Vec2 postion)
{
    _targetPosition = postion;
	if (_targetPosition == _lastPosition)
	{
		return;
	}
    else if (_isKoalaAimate)
    {
        _body->stopAllActions();
        _isKoalaAimate = false;
        _lastPosition = this->getPosition();
        this->move(postion);
    }
	FiniteTimeAction *moveV1 = NULL;
	FiniteTimeAction *moveV2 = NULL;
	FiniteTimeAction *turn1 = NULL;
	FiniteTimeAction *turn2 = NULL;
	FiniteTimeAction *moveH = NULL;
	Vec2 movePos;
	bool leftDirection = postion.x < _lastPosition.x?true:false;
	float durationY = 0;
	float durationX = 0;
	
	//�ڵ�һ��
	if (_targetPosition.y == _lastPosition.y && _lastPosition.y == _originPosition.y)
	{
		//front to us
		if (_state == k_koala_normal)
		{
			turn1 = this->getActionForState(k_koala_front_turn_left);
			moveH = this->getActionForState(k_koala_move_left);
            turn2 = this->getActionForState(k_koala_right_turn_back);
            _body->runAction(Sequence::create(turn1,moveH,turn2,CallFunc::create([=](){
                _isKoalaAimate = false;
            }),NULL));
		}
		//back to us
		else
		{
			moveH = this->getActionForState(k_koala_move_left);
            _body->runAction(Sequence::create(turn1,moveH,CallFunc::create([=](){
                _isKoalaAimate = false;
            }),NULL));
		}
		
	}
	//not in 1 floor,but floor is the same.
	else if (_targetPosition.y == _lastPosition.y && _lastPosition.y == _originPosition.y)
	{
		moveV1 = this->getActionForState(k_koala_down_ladder);
		if (_state == k_koala_normal)
		{
			turn1 = this->getActionForState(k_koala_front_turn_left);
			moveH = this->getActionForState(k_koala_move_left);
			turn2 = this->getActionForState(k_koala_right_turn_back);
			moveV1 = this->getActionForState(k_koala_up_ladder);
            _body->runAction(Sequence::create(turn1,moveH,turn2,moveV1,CallFunc::create([=](){
                _isKoalaAimate = false;
            }),NULL));
		}
		else
		{
			moveV1 = this->getActionForState(k_koala_down_ladder);
			turn1 = this->getActionForState(leftDirection?k_koala_back_turn_left:k_koala_back_turn_right);
			moveH = this->getActionForState(k_koala_move_left);
			turn2 = this->getActionForState(leftDirection?k_koala_left_turn_back:k_koala_right_turn_back);
			moveV2 = this->getActionForState(k_koala_up_ladder);
            _body->runAction(Sequence::create(moveV1,turn1,moveH,turn2,moveV2,CallFunc::create([=](){
                _isKoalaAimate = false;
            }),NULL));
		}

		_body->runAction(Sequence::create(turn1,moveH,NULL));
	}
	else if (_targetPosition.x == _lastPosition.x)
	{
		if (_targetPosition.y == _originPosition.y)
		{
			moveV1 = this->getActionForState(k_koala_down_ladder);
            _body->runAction(Sequence::create(moveV1,CallFunc::create([=](){
                _isKoalaAimate = false;
            }), NULL));
		}
		else
		{
			moveV1 = this->getActionForState(k_koala_down_ladder);
			auto back = this->getActionForState(k_koala_back);
            _body->runAction(Sequence::create(moveV1,back,CallFunc::create([=](){
                _isKoalaAimate = false;
            }),NULL));
		}
	}
    else
    {
        if (_state == k_koala_normal) {
            turn1 = this->getActionForState(k_koala_front_turn_left);
            moveH = this->getActionForState(k_koala_move_left);
            turn2 = this->getActionForState(k_koala_right_turn_back);
            moveV1 = this->getActionForState(k_koala_up_ladder);
            _body->runAction(Sequence::create(moveH,turn2,moveV1,CallFunc::create([=](){
                _isKoalaAimate = false;
            }),NULL));
    }
    }
}


void Koala::onAnimationDone()
{
	_body->stopAllActions();
}

FiniteTimeAction* Koala::getDoneAction()
{
	return Animate::create(Animation::create());
}