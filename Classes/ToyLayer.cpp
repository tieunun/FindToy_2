#include "ToyLayer.h"
#include "GameConfigure.h"
#include "Ladder.h"
#include "GameScene.h"
#include "PlayToyScene.h"
#define  Toy_Speed 300.0f;

ToyLayer::ToyLayer()
{

}

ToyLayer::~ToyLayer()
{

}

bool ToyLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}
//	this->initPutOnPositions();

	auto ladder = Ladder::create();
	this->addChild(ladder);
	ladder->setPosition(613,335);

	_toyPositions = GameConfigure::getInstance()->getToyPosition();
	_koala = Koala_::create();
	this->addChild(_koala,10);
	_koala->setPosition(386,182);
    _koala->setOriginPos(_koala->getPosition());
    _koala->setTargetPos(_koala->getPosition());
    _koala->setLadder(ladder);

	for (int i = 0 ;i < k_toy_count;i++)
	{
		auto toy = BaseToy::create((ToyType)i);
		toy->setAnchorPoint(Vec2(0,0));
		toy->setScale(.8f);
		_toies.pushBack(toy);
		this->addChild(toy);
		toy->setVisible(false);
	}

	
	return true;
}

void ToyLayer::onEnter()
{
	BaseLayer::onEnter();
	for (auto toy :_toies)
	{
		toy->setVisible(false);
	}
}

void ToyLayer::moveKoala(cocos2d::Vec2 position)
{
    _koala->move(position);
}

void ToyLayer::checkAnyToyInPosition(Vec2 position)
{

}

void ToyLayer::putOnToy()
{
}

void ToyLayer::initPutOnPositions()
{
}
//
void ToyLayer::setShouldDrawerTouched(bool touched)
{
}

void ToyLayer::openDrawer(Vec2 position)
{
    auto scene = (GameScene *)this->getParent();
    scene->openDrawer(position);
}

void ToyLayer::handInToy(ToyType type)
{
    _koala->handInToy(type);
}

void ToyLayer::handIn(ToyType type)
{
	static auto deskTopPos = Vec2(230,360);
	auto toyPos = _koala->getPosition()+Vec2(50,-20);
	auto toy = _toies.at(type);
	toy->setPosition(toyPos);
	toy->setVisible(true);
	auto move = MoveTo::create(toyPos.distance(deskTopPos)/300.0f,deskTopPos);
	auto rotate = RotateBy::create(toyPos.distance(deskTopPos)/300.0f,720);
	auto action = toy->runAction(rotate);
	action->setTag(106);
	toy->runAction(Sequence::create(move,CallFunc::create([=](){

		toy->stopAllActions();
		toy->setRotation(0);
		SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
		auto secen = PlayToyScene::create(type);
		Director::getInstance()->pushScene(TransitionFade::create(1.5,secen));
	}),NULL));
}