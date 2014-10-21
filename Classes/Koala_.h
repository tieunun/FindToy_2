//
//  Koala_.h
//  FindToy
//
//  Created by yzl on 14-10-17.
//
//

#ifndef __FindToy__Koala___
#define __FindToy__Koala___

#include "BaseNode.h"
#include "Ladder.h"
#include "KoalaState.h"
#include "BaseToy.h"
class KoalaState_;
class Koala_:public BaseNode
{
public:
    Koala_();
    ~Koala_();
    CREATE_FUNC(Koala_);
    virtual void onEnter();
    virtual bool init();
    void    changeState(KoalaState_ *state);
    void    move(Vec2 target);
    CC_SYNTHESIZE_READONLY(Sprite*, _body, Body);
    CC_SYNTHESIZE(Vec2,_targetPos,TargetPos);
    CC_SYNTHESIZE(Vec2, _originPos, OriginPos);
    CC_SYNTHESIZE(Ladder*, _ladder, Ladder);
    CC_SYNTHESIZE(bool, _isFindLadder, FindLadder);  //考拉首先要找到梯子
    CC_SYNTHESIZE(bool, _isFindToy, FindToy);
    
    Vec2    getNextMove();              //获取状态切换时下一次的步行
    Vec2    getNextRelativeMove();
    float   getMoveDuration();          //获取移动的时间
    void    openDrawer();               //if koala get the position,open the drawer
    void    handInToy(ToyType type);    //if koala get the gift,put it on the desk
private:
    
    void                moveInternel();
    std::vector<Vec2>   _reachablePositions;
    KoalaState_         *_state;
	ToyType				_handInToy;
};

#endif /* defined(__FindToy__Koala___) */
