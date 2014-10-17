#include "ToyGrab.h"
#define Toy_Grab_Speed 300

ToyGrab::ToyGrab()
{
	_type = ToyType::k_toy_frog;
	_toyAnimate = false;
}

ToyGrab::~ToyGrab()
{

}

void ToyGrab::onEnter()
{
    BaseNode::onEnter();
    
    _grabber = ToyGrabber::create();
	_grabber->setPosition(-316,126);
	this->addChild(_grabber);

	_body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("toy_grab"));
	this->addChild(_body);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ToyGrab::onGrabTouched,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}

bool ToyGrab::onGrabTouched(Touch *touch,Event *event)
{
	if (!_toyAnimate)
	{
		_toyAnimate = true;
		this->play();
	}
	return true;
}

void ToyGrab::play()
{
	auto winSize = Director::getInstance()->getWinSize();
	auto move1 = MoveBy::create((winSize.width/2+300)/Toy_Grab_Speed,Vec2(-winSize.width/2-300,0));
	auto move2 = MoveBy::create((winSize.width+600)/Toy_Grab_Speed,Vec2(winSize.width+600,0));
	auto move3 = move1->clone();

	this->runAction(Sequence::create(move1,
		CallFunc::create([=](){
			this->setGrabFlippedX(true);
	}),
		move2,
		CallFunc::create([=](){
			this->setGrabFlippedX(false);
	}),
		move3,
		CallFunc::create([=](){
			_toyAnimate = false;
	}),
		NULL
		));
}

void ToyGrab::setGrabFlippedX(bool flipped)
{
	if (flipped)
	{
		_body->setFlippedX(true);
		_grabber->setGrabberFlippedX(true);
		_grabber->setPositionX(316);
	}
	else
	{
		_body->setFlippedX(false);
		_grabber->setGrabberFlippedX(false);
		_grabber->setPositionX(-316);
	}
}