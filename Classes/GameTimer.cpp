#include "GameTimer.h"
#include "SimpleAudioEngine.h"
#include "GameTimeLayer.h"
using namespace CocosDenshion;

GameTimer::GameTimer()
{
	_speed = 1;
	_time = 75;
}

GameTimer::~GameTimer()
{

}

bool GameTimer::init()
{
	if (!BaseNode::init())
	{
		return false;
	}
	auto temp = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("game_timer_blood"));
	_timer = ProgressTimer::create(temp);
	_timer->setType(ProgressTimer::Type::BAR);
	_timer->setMidpoint(Vec2(0,0));
	_timer->setBarChangeRate(Vec2(1,0));
	_timer->setPercentage(100);
	_timer->setPosition(22,-5);
	this->setContentSize(temp->getContentSize());
	this->addChild(_timer);

	auto bg = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("game_timer_bg"));
	this->addChild(bg);

	auto rotate1 = RotateBy::create(.6f,3);
	auto rotate2 = RotateBy::create(1.2f,-6);
	this->runAction(RepeatForever::create(Sequence::create(rotate1,rotate2,rotate1,NULL)));

	auto move1 = MoveBy::create(.6f,Vec2(0,-10));
	auto move2 = MoveBy::create(1.2f,Vec2(0,20));
	this->runAction(RepeatForever::create(Sequence::create(move1,move2,move1,NULL)));

	_label = Label::createWithCharMap("common_number.png",31.2,36,'0');
	this->addChild(_label);
	_label->setPosition(270,-5);

	return true;
}

void GameTimer::onEnter()
{
	BaseNode::onEnter();
	this->scheduleUpdate();
}

void GameTimer::update(float dt)
{
	static bool blink = false;
	static bool countdown = false;
	if (_timer->getPercentage()<=0.00001)
	{
		auto layer = (GameTimeLayer*)this->getParent();
		SimpleAudioEngine::getInstance()->stopAllEffects();
		layer->showGameOver();
		_label->stopAllActions();
		this->unscheduleUpdate();
	}
	auto time = (int)(_timer->getPercentage()*_time/100);
    _label->setString(StringUtils::format("%d",time));
	if (blink)
	{
		if (countdown)
		{
			return;
		}
		else
		{
			if (_timer->getPercentage()<10)
			{
				countdown = true;
				_label->runAction(RepeatForever::create(Blink::create(1,2)));
				SimpleAudioEngine::getInstance()->playEffect("timer_count_down.mp3",true);
			}
		}
	}
	else
	{
		if (_timer->getPercentage()<30)
		{
			_timer->runAction(Blink::create(1.5f,5));
			blink = true;
		}
	}
	
}

void GameTimer::BeginToTime(float time)
{
	if (time != 0)
	{
		_time = time;
	}
	_label->setString(StringUtils::format("%d",(int)time));
	_timer->stopAllActions();
	_timer->setPercentage(100);
	auto progressTo = ProgressTo::create(_time/_speed,0);
	_timer->runAction(progressTo);
}