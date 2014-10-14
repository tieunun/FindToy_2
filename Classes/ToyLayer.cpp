#include "ToyLayer.h"
#include "GameConfigure.h"

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

	for (int i = 0 ;i < k_toy_count;i++)
	{
		auto toy = BaseToy::create((ToyType)i);
		
		_toies.pushBack(toy);
		this->addChild(toy);
		toy->setVisible(false);
	}

	_toyPositions = GameConfigure::getInstance()->getToyPosition();
	_koala = Koala::create();
	this->addChild(_koala);
	_koala->setPosition(386,182);
    _koala->setOriginPosition(_koala->getPosition());
    _koala->setLastPosition(_koala->getPosition());

	return true;
}

void ToyLayer::moveKoala(cocos2d::Vec2 position)
{
    static Vec2 startPos = Vec2(605,182);
    auto resultPos = Vec2(startPos.x+185*position.x,startPos.y+113*position.y);
    _koala->move(resultPos);
}