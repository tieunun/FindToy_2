//
//  Koala_.cpp
//  FindToy
//
//  Created by yzl on 14-10-17.
//
//

#include "Koala_.h"
#include"ToyLayer.h"
#define Koala_Speed 200.0f


Koala_::Koala_()
{
    _state = nullptr;
	_isFindToy = false;
	_isFindLadder = false;
    _targetPos = Vec2(0,0);
    _originPos = Vec2(0,0);
    for (int i = 0; i < 16; i++) {
        auto pos = GAME_DATA_POINT(StringUtils::format("koala_position_%d",i));
        _reachablePositions.push_back(pos);
    }
}

bool Koala_::init()
{
    if(!BaseNode::init())
        return false;
    _body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("koala"));
    this->addChild(_body);
    _state = new KoalaStateNormal();
    _targetPos = this->getPosition();
	    
    return true;
}

Koala_::~Koala_()
{}

void Koala_::onEnter()
{
    BaseNode::onEnter();

	this->changeState(new KoalaStateNormal());
}

void Koala_::changeState(KoalaState_ *state)
{
    if (_state) {
        delete _state;
        _state = nullptr;
    }
    _state = state;
    this->moveInternel();
}

Vec2 Koala_::getNextMove()
{
    auto curPos = this->getPosition();
    
    if (curPos == _targetPos) {
        return curPos;
    }
   
    if (curPos.y == _targetPos.y) {
        if (curPos.y != _originPos.y) {
            //|  |
            //|__| like this
            return Vec2(curPos.x,_originPos.y);
        }
        else
        {
            //____ like this
            //and decide the koala got the ladder
            if (this->getPosition() == Vec2(605+180*_ladder->getLadderPos(),_originPos.y))
            {
                if(!_isFindToy)
                {
                    _isFindLadder = true;
                }
                else
                {
                    _isFindLadder = false;
                }
                
            }
            if (_isFindLadder && !_isFindToy) {
                return _targetPos;
            }
            else if (_isFindLadder&& _isFindToy)
            {
                return Vec2(605+180*_ladder->getLadderPos(),_originPos.y);
            }
            else if (!_isFindLadder && _isFindToy)
            {
                return _targetPos;
            }
            else if (!_isFindLadder && !_isFindToy)
            {
                return Vec2(605+180*_ladder->getLadderPos(),_originPos.y);
            }
        }
    }
    else
    {
        if (curPos.x == _targetPos.x) {
            //|
            //| like this
            return _targetPos;
        }
        else
        {
            if (curPos.y == _originPos.y) {
                //  |
                //__| like this
                
                if (this->getPosition() == Vec2(605+180*_ladder->getLadderPos(),_originPos.y)) {
                    _isFindLadder = true;
                }
                if (_isFindLadder) {
                    return Vec2(_targetPos.x,_originPos.y);
                }
                else
                {
                    return Vec2(605+180*_ladder->getLadderPos(),_originPos.y);
                }
            }
            else
            {
                //|                |
                //|__ like this or |_|
                return Vec2(curPos.x,_originPos.y);
            }
        }
    }
}

Vec2 Koala_::getNextRelativeMove()
{
    return this->getNextMove() - this->getPosition();
}

float Koala_::getMoveDuration()
{
    auto pos = this->getNextRelativeMove();
    if (pos.x!=0) {
        return abs(pos.x)/Koala_Speed;
    }
    else
    {
        return abs(pos.y)/Koala_Speed;
    }
}

void Koala_::move(cocos2d::Vec2 target)
{
    auto targetPos = _reachablePositions[target.x+target.y*4];
    _targetPos = targetPos;
    this->moveInternel();
}

void Koala_::moveInternel()
{
    _state->handle(this);
}

void Koala_::openDrawer()
{
	auto layer = (ToyLayer*)this->getParent();
	if (_isFindToy)
	{
		_isFindToy = false;
		this->changeState(new KoalaStateNormal());
		layer->handIn(_handInToy);
	}
	else
	{
		int index = 0;
		for (auto item : _reachablePositions) {
			if (item == _targetPos) {
				break;
			}
			index++;
		}
		layer->openDrawer(Vec2(index%4,index/4));
	}
}

void Koala_::handInToy(ToyType type)
{
	_handInToy = type;
    _targetPos = _originPos;
    _isFindToy = true;
    this->moveInternel();
}
