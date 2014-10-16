#include "PlayToyScene.h"

PlayToyScene::PlayToyScene()
{

}

PlayToyScene::~PlayToyScene()
{

}

PlayToyScene *PlayToyScene::create(ToyType toyType)
{
	auto scene = new PlayToyScene();
	scene->_toyType = toyType;
	scene->init();
	scene->autorelease();
	return scene;
}

bool PlayToyScene::init()
{
	if (!BaseScene::init())
	{
		return false;
	}

	_backgroundLayer = PlayToyBackground::create(_toyType);
	_playLayer		 = PlayToyPlayLayer::create(_toyType);
	this->addChild(_backgroundLayer);
	this->addChild(_playLayer);
	return true;
}

void PlayToyScene::moveBackground()
{
	_backgroundLayer->move();
}

void PlayToyScene::moveHelicopter()
{
	_playLayer->moveHelicopter();
}

void PlayToyScene::stopBackgroundMove()
{
    _backgroundLayer->stopAllActions();
}