#include "GameStaticLayer.h"
#include "Shelf.h"
#include "Desk.h"
#include "ToyPistol.h"
#include "ToyHarmonica.h"
#include "ToyTransformer.h"
#include "ToyPanda.h"
#include "ToyFrog.h"
#include "ToyDoll.h"
#include "Koala.h"
#include "GameScene.h"

GameStaticLayer::GameStaticLayer()
{

}

GameStaticLayer::~GameStaticLayer()
{

}

bool GameStaticLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	auto shelf = Shelf::create();
	auto shelfPos = GAME_DATA_POINT("shelf_position");
	shelf->setPosition(this->getPositionInWinSize(shelfPos));
	this->addChild(shelf);

	auto desk = Desk::create();
	auto deskPos = GAME_DATA_POINT("desk_position");
	desk->setPosition(this->getPositionInWinSize(deskPos));
	this->addChild(desk);

// 	auto toy = ToyFrog::create();
// 	this->addChild(toy,1,2);
// 	toy->setPosition(_winSize/2);
//	auto koala = Koala::create();
//	this->addChild(koala);
//	koala->setPosition(_winSize/2);
//
// 	auto listenter = EventListenerTouchOneByOne::create();
// 	listenter->setSwallowTouches(false);
// 	listenter->onTouchBegan = CC_CALLBACK_2(GameStaticLayer::abcdefg,this);
// 	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listenter,toy);

	return true;
}

bool GameStaticLayer::abcdefg(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
//     auto toy = (ToyPistol*)this->getChildByTag(2);
//     toy->play();
// // 	auto toy = ToyDoll::create();
// // 	toy->play();
    return true;
}

void GameStaticLayer::onDrawerTouched(cocos2d::Vec2 position)
{
    auto scene = (GameScene*)this->getParent();
    scene->moveKoala(position);
}



