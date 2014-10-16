#pragma once
#include "BaseToy.h"
#include "ToyGrabber.h"
class ToyGrab:public BaseToy
{
public:
	ToyGrab();
	~ToyGrab();

	CREATE_FUNC(ToyGrab);
	virtual void onEnter();
	virtual void play();
    
private:
    ToyGrabber *_grabber;
};