#include "Koala.h"
#include "ToyLayer.h"
#define Koala_Speed 100.0f

Koala::Koala()
{
    _lastPosition = Vec2(0,0);
    _targetPosition = Vec2(0,0);
    _originPosition = Vec2(0,0);
    _isKoalaAimate = false;
    _state = k_koala_normal;
	_isFirstMove = true;
	_getGift = false;
}

Koala::~Koala()
{

}

void Koala::onEnter()
{
	BaseNode::onEnter();

	if (_onEnterCount<=1)
	{
		_body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("koala"));
		this->addChild(_body);
	}
}

void Koala::setState(const KoalaState state)
{
	_state = state;
}

KoalaState Koala::getState() const
{
	return _state;
}

FiniteTimeAction *Koala::getActionForState(const KoalaState state,Vec2 movePos)
{
	Animation *animation = NULL;
	
	auto durationX = abs(movePos.x) / Koala_Speed;
	auto durationY = abs(movePos.y)/Koala_Speed;
	switch (state)
	{
	case k_koala_normal:
		animation = AnimationCache::getInstance()->getAnimation("koala_animation_normal");
		return Spawn::create(Animate::create(animation),this->getCallAction(state),NULL);
		break;
	case k_koala_smile:
		animation = AnimationCache::getInstance()->getAnimation("koala_animation_smile");
		return Spawn::create(Animate::create(animation),this->getCallAction(state),NULL);
		break;
	case  k_koala_at_ladder:
		{
			_body->setFlippedX(false);
			animation = AnimationCache::getInstance()->getAnimation("koala_animation_at_ladder");
			return Spawn::create(Animate::create(animation),this->getCallAction(state),NULL);
		}
		break;
	case  k_koala_up_ladder:
	case k_koala_down_ladder:
		{
			return Sequence::create(Spawn::create(this->getCallAction(state),CallFunc::create([=](){
				_body->setFlippedX(false);

			}),MoveBy::create(durationY,Vec2(0,movePos.y)),CallFunc::create([=](){
                //_body->stopAllActions();
                auto animation = AnimationCache::getInstance()->getAnimation("koala_animation_up_ladder");
                auto animate = Animate::create(animation);
                animate->setTag(state);

                _body->runAction(animate);
            }),NULL),CallFunc::create([=](){
                _body->stopActionByTag(state);
            }), NULL);
		}
		break;
	case k_koala_down_with_gift:
		{
			return Sequence::create(Spawn::create(this->getCallAction(state),CallFunc::create([=](){
				_body->setFlippedX(false);

			}),MoveBy::create(durationY,Vec2(0,movePos.y)),CallFunc::create([=](){
				//_body->stopAllActions();
				auto animation = AnimationCache::getInstance()->getAnimation("koala_animation_down_ladder_gift");
				auto animate = Animate::create(animation);
				animate->setTag(state);

				_body->runAction(animate);
			}),NULL),CallFunc::create([=](){
				_body->stopActionByTag(state);
			}), NULL);
		}
		break;
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
           
			auto internelState = movePos.x<0?k_koala_move_left:k_koala_move_right;
			
//			_body ->runAction(Animate::create(animation));
			auto moveH = MoveBy::create(durationX,Vec2(movePos.x,0));
            return Sequence::create( Spawn::create(CallFunc::create([=](){
				if (internelState == k_koala_move_right)
				{
					_body->setFlippedX(false);
				}
				else
				{
					_body->setFlippedX(true);
				}
               auto animation = AnimationCache::getInstance()->getAnimation("koala_animation_move_right");
                auto animate = Animate::create(animation);
                animate->setTag(state);
				if (_isFirstMove)
				{
					auto delay = DelayTime::create((movePos.x-180*_drawerPosition.x)/Koala_Speed);
					auto ladderMove = MoveBy::create(180*_drawerPosition.x/Koala_Speed,Vec2(180*_drawerPosition.x,0));
					_ladder->runAction(Sequence::create(delay,ladderMove,NULL));
				}
				else
				{
					auto ladderMove = MoveBy::create(durationX,Vec2(movePos.x,0));
					_ladder->runAction(ladderMove);
				}
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
	if (_targetPosition == _lastPosition &&_getGift)
	{
        auto normal = this->getActionForState(k_koala_normal);
        _body->runAction(Sequence::create(normal,this->getCallAction(k_koala_normal),CallFunc::create([=](){
            _isKoalaAimate = false;
            _isFirstMove = false;
            this->onReachDrawer();

        }),NULL));
        return;
	}
    else if (_targetPosition == _lastPosition &&!_getGift)
    {
		auto layer = (ToyLayer*)this->getParent();
		layer->checkAnyToyInPosition(_drawerPosition);
        return;
    }
    else if (_isKoalaAimate)
    {
		return;
        _body->stopAllActions();
		
        _isKoalaAimate = false;

        _lastPosition = this->getPosition()+_body->getPosition();
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
	
	//int the floor 1
	if (_targetPosition.y == _lastPosition.y && _lastPosition.y == _originPosition.y)
	{
		//front to us
		if (_state == k_koala_normal)
		{
			turn1 = this->getActionForState(k_koala_front_turn_left);
			moveH = this->getActionForState(k_koala_move_left,Vec2(_targetPosition.x-_lastPosition.x,0));
            turn2 = this->getActionForState(k_koala_right_turn_back);
            _body->runAction(Sequence::create(turn1,moveH,turn2,CallFunc::create([=](){
                _isKoalaAimate = false;
				_isFirstMove = false;
				this->onReachDrawer();
            }),NULL));
		}
		//back to us
		else
		{
			if (_targetPosition.x > _lastPosition.x)
			{
				turn1 = this->getActionForState(k_koala_front_turn_right);
			}
			else
			{
				turn1 = this->getActionForState(k_koala_front_turn_left);
			}
			auto back = this->getActionForState(k_koala_back);
			moveH = this->getActionForState(k_koala_move_left,Vec2(_targetPosition.x-_lastPosition.x,0));
            _body->runAction(Sequence::create(turn1,moveH,back,CallFunc::create([=](){
                _isKoalaAimate = false;
				_isFirstMove = false;
				this->onReachDrawer();
            }),NULL));
		}
		
	}
	//
	else if (_targetPosition.x!=_lastPosition.x)
	{
		//moveV1 = this->getActionForState(k_koala_down_ladder);
		if (_state == k_koala_normal)
		{
			turn1 = this->getActionForState(k_koala_front_turn_left);
			moveH = this->getActionForState(k_koala_move_left,Vec2(_targetPosition.x-_lastPosition.x,0));
			turn2 = this->getActionForState(k_koala_right_turn_back);
			moveV1 = this->getActionForState(k_koala_up_ladder,Vec2(0,_targetPosition.y-_originPosition.y));
			auto atLadder = this->getActionForState(k_koala_at_ladder);
            _body->runAction(Sequence::create(turn1,moveH,turn2,moveV1,atLadder,CallFunc::create([=](){
                _isKoalaAimate = false;
				_isFirstMove = false;
				this->onReachDrawer();
            }),NULL));
		}
		else
		{
			moveV1 = this->getActionForState(k_koala_down_ladder,Vec2(0,_originPosition.y-_lastPosition.y));
			turn1 = this->getActionForState(leftDirection?k_koala_back_turn_left:k_koala_back_turn_right);
			moveH = this->getActionForState(k_koala_move_left,Vec2(_targetPosition.x-_lastPosition.x,0));
			turn2 = this->getActionForState(leftDirection?k_koala_left_turn_back:k_koala_right_turn_back);
			moveV2 = this->getActionForState(k_koala_up_ladder,Vec2(0,_targetPosition.y-_originPosition.y));
			auto back = this->getActionForState(k_koala_back);
			auto atLadder = this->getActionForState(k_koala_at_ladder);
			if (_targetPosition.y == _originPosition.y)
			{
				_body->runAction(Sequence::create(moveV1,turn1,moveH,turn2,moveV2,back,CallFunc::create([=](){
					_isKoalaAimate = false;
					_isFirstMove = false;
					this->onReachDrawer();
				}),NULL));
			}
			else
			{
				_body->runAction(Sequence::create(moveV1,turn1,moveH,turn2,moveV2,atLadder,CallFunc::create([=](){
					_isKoalaAimate = false;
					_isFirstMove = false;
					this->onReachDrawer();
				}),NULL));
			}
           
		}

		//_body->runAction(Sequence::create(turn1,moveH,NULL));
	}
	else if (_targetPosition.x == _lastPosition.x)
	{
		if (_targetPosition.y == _originPosition.y)
		{
			if (!_getGift)
			{
				moveV1 = this->getActionForState(k_koala_down_ladder,Vec2(0,_targetPosition.y-_lastPosition.y));
				auto back = this->getActionForState(k_koala_back);
				_body->runAction(Sequence::create(moveV1,back,CallFunc::create([=](){
					_isKoalaAimate = false;
					_isFirstMove = false;
					this->onReachDrawer();
				}), NULL));
			}
			
			else
			{
				moveV1 = this->getActionForState(k_koala_down_with_gift,Vec2(0,_targetPosition.y-_lastPosition.y));
				turn1 = this->getActionForState(k_koala_back_turn_right);
				turn2 = this->getActionForState(k_koala_right_turn_front);
				auto normal = this->getActionForState(k_koala_normal);
				_body->runAction(Sequence::create(moveV1,normal,CallFunc::create([=](){
					_isKoalaAimate = false;
					_isFirstMove = false;
					this->onReachDrawer();
				}), NULL));

			}
		}
		else if (_targetPosition.y > _lastPosition.y)
		{
			moveV1 = this->getActionForState(k_koala_up_ladder,Vec2(0,_targetPosition.y-_lastPosition.y));
			auto atLadder = this->getActionForState(k_koala_at_ladder);
            _body->runAction(Sequence::create(moveV1,atLadder,CallFunc::create([=](){
                _isKoalaAimate = false;
				_isFirstMove = false;
				this->onReachDrawer();
            }),NULL));
		}
		else 
		{
			if (_targetPosition.y != _originPosition.y)
			{
				moveV1 = this->getActionForState(k_koala_up_ladder,Vec2(0,_targetPosition.y-_lastPosition.y));
				auto atLadder = this->getActionForState(k_koala_at_ladder);
				_body->runAction(Sequence::create(moveV1,atLadder,CallFunc::create([=](){
					_isKoalaAimate = false;
					_isFirstMove = false;
					this->onReachDrawer();
				}),NULL));
			}
		}
	}
    else
    {
        if (_state == k_koala_normal) {
            turn1 = this->getActionForState(k_koala_front_turn_left);
            moveH = this->getActionForState(k_koala_move_left,Vec2(_targetPosition.x-_originPosition.x,0));
            turn2 = this->getActionForState(k_koala_right_turn_back);
            moveV1 = this->getActionForState(k_koala_up_ladder,Vec2(0,_targetPosition.y-_originPosition.y));
			auto atLadder = this->getActionForState(k_koala_at_ladder); 
            _body->runAction(Sequence::create(turn1,moveH,turn2,moveV1,atLadder,CallFunc::create([=](){
                _isKoalaAimate = false;
				_isFirstMove = false;
				this->onReachDrawer();
            }),NULL));
        }
        else
        {
            moveV1 = this->getActionForState(k_koala_down_ladder);
            turn1 = this->getActionForState(k_koala_front_turn_left);
            moveH = this->getActionForState(k_koala_move_left);
            moveV2 = this->getActionForState(k_koala_up_ladder);
            _body->runAction(Sequence::create(moveV1,turn1,moveH,moveV2,CallFunc::create([=](){
                _isKoalaAimate = false;
				_isFirstMove = false;
				this->onReachDrawer();
            }),NULL));
        }
    }
    _lastPosition = _targetPosition;
	_isKoalaAimate = true;
}


void Koala::onAnimationDone()
{
	_body->stopAllActions();
}

FiniteTimeAction* Koala::getDoneAction()
{
	return Animate::create(Animation::create());
}

void Koala::onReachDrawer()
{
	if (!_getGift)
	{
		auto layer = (ToyLayer*)this->getParent();
		layer->checkAnyToyInPosition(_drawerPosition);
		//Director::getInstance()->getEventDispatcher()->setEnabled(true);
	}
	else
	{
		_getGift = false;
		auto layer = (ToyLayer*)this->getParent();
		layer->putOnToy();
	}
}

void Koala::moveDownWithGift()
{
	_getGift = true;
	this->move(Vec2(_lastPosition.x,_originPosition.y));
}

Vec2 Koala::getBodyPosition()
{
	return this->getPosition() + _body->getPosition();
}