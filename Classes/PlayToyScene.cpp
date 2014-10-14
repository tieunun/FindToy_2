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
	return true;
}