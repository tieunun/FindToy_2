#include "GameStaticLayer.h"
#include "Shelf.h"
#include "Desk.h"
#include "ToyPistol.h"
#include "ToyHarmonica.h"

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

	auto toy = ToyHarmonica::create();
	this->addChild(toy,1,2);
	toy->setPosition(_winSize/2);
    

	return true;
}

bool GameStaticLayer::abcdefg(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    auto toy = (ToyPistol*)this->getChildByTag(2);
    toy->play();
    return true;
}



