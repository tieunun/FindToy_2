#include "GameTimeLayer.h"
#include "GameScene.h"

GameTimeLayer::GameTimeLayer()
{

}

GameTimeLayer::~GameTimeLayer()
{

}

bool GameTimeLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	auto pause_nor = Sprite::createWithSpriteFrameName("pause.png");
	auto pause_sel = Sprite::createWithSpriteFrameName("pause.png");
	pause_nor->setScale(.5f);
	pause_sel->setScale(.6f);
	auto pauseItem = MenuItemSprite::create(pause_nor,pause_sel,CC_CALLBACK_0(GameTimeLayer::showPause,this));
	auto menu = Menu::create(pauseItem,NULL);
	this->addChild(menu);
	menu->setPosition(80,700);

	_gameTimer = GameTimer::create();
	this->addChild(_gameTimer);
	_gameTimer->setPosition(340,680);

	return true;
}

void GameTimeLayer::onEnter()
{
	BaseLayer::onEnter();
	_gameTimer->BeginToTime();
}

void GameTimeLayer::showGameOver()
{
	auto scene = (GameScene*)this->getParent();
	scene->showGameOver();
}

void GameTimeLayer::showPause()
{
	auto scene = (GameScene*)this->getParent();
	scene->showPause();
}