//
//  ToyGrabber.cpp
//  FindToy
//
//  Created by yzl on 14-10-16.
//
//

#include "ToyGrabber.h"

ToyGrabber::ToyGrabber()
{
}

ToyGrabber::~ToyGrabber()
{
    
}

void ToyGrabber::onEnter()
{
    BaseNode::onEnter();
    
    _body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("toy_grabber"));
    this->addChild(_body);
    this->play();
}

void ToyGrabber::play()
{
    auto animation = AnimationCache::getInstance()->getAnimation("toy_grab_animation");
    _body->runAction(Animate::create(animation)->reverse());
}

void ToyGrabber::setGrabberFlippedX(bool flipped)
{
	if (flipped)
	{
		_body->setFlippedX(true);
	}
	else
	{
		_body->setFlippedX(false);
	}
}