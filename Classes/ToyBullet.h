//
//  ToyBullet.h
//  FindToy
//
//  Created by yzl on 14-10-15.
//
//

#ifndef __FindToy__ToyBullet__
#define __FindToy__ToyBullet__

#include "BaseToy.h"

class ToyBullet:public BaseToy
{
public:
    ToyBullet();
    ~ToyBullet();
    CREATE_FUNC(ToyBullet);
    virtual void onEnter();
    void play();
private:
    bool OnToyTouched(Touch *touch,Event *event);
   // void update(float dt);
    
};

#endif /* defined(__FindToy__ToyBullet__) */
