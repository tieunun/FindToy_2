//
//  KoalaState.cpp
//  FindToy
//
//  Created by yzl on 14-10-17.
//
//

#include "KoalaState.h"
#include"Koala_.h"

KoalaState_::KoalaState_()
{}

KoalaState_::~KoalaState_()
{}

void KoalaState_::handleInternel(Koala_ *koala)
{
    auto pos = koala->getNextRelativeMove();
    auto realPos = koala->getNextMove();
    if (pos.x && pos.y) {
        log("can not move inclined");
        return;
    }
    else if (!pos.x && !pos.y)
    {
        if (koala->getOriginPos().y != koala->getTargetPos().y) {
            koala->changeState(new KoalaStateAtLadder());
        }
        else
        {
            koala->changeState(new KoalaStateBack());
        }
        return;
    }
    if (pos.x != 0) {
        
        koala->changeState(new KoalaStateHorizontalMove());
    }
    else
    {
        koala->changeState(new KoalaStateLadderMove());
    }
}

KoalaStateNormal::KoalaStateNormal()
{
}

KoalaStateNormal::~KoalaStateNormal()
{}

void KoalaStateNormal::handle(Koala_ *koala)
{
    koala->runAction(Sequence::create(CallFunc::create([=](){
        koala->getBody()->setFlippedX(false);
        koala->stopAllActions();
        koala->getBody()->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation("koala_animation_normal");
        koala->getBody()->runAction(Animate::create(animation));
    }),
                                      CallFunc::create([=](){

        if(koala->getPosition()!=koala->getTargetPos())
        {
            this->handleInternel(koala);
        }
    }),
                                      NULL));
    
}

KoalaStateBack::KoalaStateBack()
{
}

KoalaStateBack::~KoalaStateBack()
{}

void KoalaStateBack::handle(Koala_ *koala)
{
    koala->runAction(Sequence::create(CallFunc::create([=](){
        koala->getBody()->setFlippedX(false);
        koala->stopAllActions();
        koala->getBody()->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation("koala_animation_back");
        koala->getBody()->runAction(Animate::create(animation));
    }),
                                      CallFunc::create([=](){
        if(koala->getPosition()!=koala->getTargetPos())
        {
            this->handleInternel(koala);
        }
        else
        {
            log("reach the position");
            koala->openDrawer();
        }
    }),
                                      NULL));
}

KoalaStateBackTurn::KoalaStateBackTurn()
{}

KoalaStateBackTurn::~KoalaStateBackTurn()
{}

void KoalaStateBackTurn::handle(Koala_ *koala)
{
    
}

KoalaStateNormalTurn::KoalaStateNormalTurn()
{}

KoalaStateNormalTurn::~KoalaStateNormalTurn()
{}

void KoalaStateNormalTurn::handle(Koala_ *koala)
{}

KoalaStateAtLadder::KoalaStateAtLadder()
{}

KoalaStateAtLadder::~KoalaStateAtLadder()
{
}

void KoalaStateAtLadder::handle(Koala_ *koala)
{
    koala->runAction(Sequence::create(CallFunc::create([=](){
        koala->getBody()->setFlippedX(false);
        koala->stopAllActions();
        koala->getBody()->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation("koala_animation_at_ladder");
        koala->getBody()->runAction(Animate::create(animation));
    }),
                                      CallFunc::create([=](){
        if (koala->getTargetPos() != koala->getPosition()) {
             this->handleInternel(koala);
        }
        else
        {
            log("reach the position");
            koala->openDrawer();
        }
    }),
                                      NULL));
}


KoalaStateLadderMove::KoalaStateLadderMove()
{}

KoalaStateLadderMove::~KoalaStateLadderMove()
{}

void KoalaStateLadderMove::handle(Koala_ *koala)
{
    koala->runAction(Sequence::create(CallFunc::create([=](){
        koala->getBody()->setFlippedX(false);
        koala->stopAllActions();
        koala->getBody()->stopAllActions();
    }),
                                      CallFunc::create([=](){
        auto animation = AnimationCache::getInstance()->getAnimation("koala_animation_up_ladder");
        koala->getBody()->runAction(Animate::create(animation));
        koala->runAction(Sequence::create(MoveTo::create(koala->getMoveDuration(), koala->getNextMove()),
                                          CallFunc::create([=](){
            this->handleInternel(koala);
        })
                                          ,NULL));
    }),
                                      NULL));
}

KoalaStateHorizontalMove::KoalaStateHorizontalMove()
{}

KoalaStateHorizontalMove::~KoalaStateHorizontalMove()
{}

void KoalaStateHorizontalMove::handle(Koala_ *koala)
{
    koala->runAction(Sequence::create(CallFunc::create([=](){
        koala->getLadder()->stopAllActions();
        koala->stopAllActions();
        koala->getBody()->stopAllActions();
    }),
                                      CallFunc::create([=](){
                auto animation = AnimationCache::getInstance()->getAnimation("koala_animation_move_right");
                koala->getBody()->runAction(Animate::create(animation));
                auto pos = koala->getNextMove();
        koala->getBody()->setFlippedX(koala->getNextRelativeMove().x<0?true:false);
        auto move = MoveTo::create(koala->getMoveDuration(), koala->getNextMove());
        if (koala->getFindLadder()) {
            koala->getLadder()->runAction(MoveBy::create(koala->getMoveDuration(), koala->getNextRelativeMove()));
        }
        koala->runAction(Sequence::create(move,CallFunc::create([=](){
            this->handleInternel(koala);
        }), NULL));
    }), NULL));
}
