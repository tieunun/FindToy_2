#include "ToyGrab.h"

ToyGrab::ToyGrab()
{
	_type = ToyType::k_toy_frog;
}

ToyGrab::~ToyGrab()
{

}

void ToyGrab::onEnter()
{
    BaseNode::onEnter();
    
    _grabber = ToyGrabber::create();
}

void ToyGrab::play()
{

}