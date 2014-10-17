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
	_shouldDrawerTouched = true;
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

	return true;
}

bool GameStaticLayer::abcdefg(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    return true;
}

void GameStaticLayer::onDrawerTouched(cocos2d::Vec2 position)
{
	//if (_shouldDrawerTouched)
	//{
		auto scene = (GameScene*)this->getParent();
		scene->moveKoala(position);
		Director::getInstance()->getEventDispatcher()->setEnabled(false);
	//}  
}



