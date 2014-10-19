//
//  KoalaState.h
//  FindToy
//
//  Created by yzl on 14-10-17.
//
//

#ifndef __FindToy__KoalaState__
#define __FindToy__KoalaState__

#include "Koala_.h"
class Koala_;
class KoalaState_ :public Ref
{
public:
    KoalaState_();
    ~KoalaState_();
    virtual void handle(Koala_ *koala)=0;
protected:
    void handleInternel(Koala_ *koala);
};

class KoalaStateNormal:public KoalaState_
{
public:
    KoalaStateNormal();
    ~KoalaStateNormal();
    virtual void handle(Koala_ *koala);;
};

class KoalaStateBack:public KoalaState_
{
public:
    KoalaStateBack();
    ~KoalaStateBack();
    virtual void handle(Koala_ *koala);;
};

class KoalaStateBackTurn:public KoalaState_
{
public:
    KoalaStateBackTurn();
    ~KoalaStateBackTurn();
    virtual void handle(Koala_ *koala);;
};

class KoalaStateNormalTurn:public KoalaState_
{
public:
    KoalaStateNormalTurn();
    ~KoalaStateNormalTurn();
    virtual void handle(Koala_ *koala);;
};

class KoalaStateAtLadder:public KoalaState_
{
public:
    KoalaStateAtLadder();
    ~KoalaStateAtLadder();
    virtual void handle(Koala_ *koala);;
};

class KoalaStateLadderMove:public KoalaState_
{
public:
    KoalaStateLadderMove();
    ~KoalaStateLadderMove();
    virtual void handle(Koala_ *koala);;
};

class KoalaStateHorizontalMove:public KoalaState_
{
public:
    KoalaStateHorizontalMove();
    ~KoalaStateHorizontalMove();
    virtual void handle(Koala_ *koala);;
};

#endif /* defined(__FindToy__KoalaState__) */
