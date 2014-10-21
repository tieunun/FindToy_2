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

	_gameTimer = GameTimer::create();
	this->addChild(_gameTimer);
	_gameTimer->setPosition(240,680);

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