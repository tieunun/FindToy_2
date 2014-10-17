//
//  ToyGrabber.h
//  FindToy
//
//  Created by yzl on 14-10-16.
//
//

#ifndef __FindToy__ToyGrabber__
#define __FindToy__ToyGrabber__

#include "BaseToy.h"

class ToyGrabber:public BaseToy
{
public:
    ToyGrabber();
    ~ToyGrabber();
    virtual void onEnter();
    CREATE_FUNC(ToyGrabber);
    virtual void play();
	void setGrabberFlippedX(bool flipped);
};

#endif /* defined(__FindToy__ToyGrabber__) */
