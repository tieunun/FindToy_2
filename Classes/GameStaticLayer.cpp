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

    _shelf = Shelf::create();
	auto shelfPos = GAME_DATA_POINT("shelf_position");
	_shelf->setPosition(this->getPositionInWinSize(shelfPos));
	this->addChild(_shelf);

	auto desk = Desk::create();
	auto deskPos = GAME_DATA_POINT("desk_position");
	desk->setPosition(this->getPositionInWinSize(deskPos));
	this->addChild(desk);
    
    _popToy = PopToy::create();
    _popToy->setVisible(false);
    this->addChild(_popToy);

	return true;
}


void GameStaticLayer::onDrawerTouched(cocos2d::Vec2 position)
{
    auto scene = (GameScene*)this->getParent();
    scene->moveKoala(position);
}

void GameStaticLayer::openDrawer(Vec2 position)
{
    _popToy->setPosition(Vec2(349,274)+Vec2(186*position.x,113*position.y));
    _shelf->openDrawer(position);
}

void GameStaticLayer::PopToy(ToyType type)
{
    _popToy->popToy(type);
    if(type>=0 && type<k_toy_count)
    {
        auto scene = (GameScene*)this->getParent();
        scene->handInToy(type);
    }
}



