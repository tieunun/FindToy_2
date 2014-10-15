#include "ToyLayer.h"
#include "GameConfigure.h"
#include "Ladder.h"
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
	this->initPutOnPositions();

	auto ladder = Ladder::create();
	this->addChild(ladder);
	ladder->setPosition(613,335);

	_toyPositions = GameConfigure::getInstance()->getToyPosition();
	_koala = Koala::create();
	this->addChild(_koala);
	_koala->setPosition(386,182);
    _koala->setOriginPosition(_koala->getPosition());
    _koala->setLastPosition(_koala->getPosition());
	_koala->setLadder(ladder);

	for (int i = 0 ;i < k_toy_count;i++)
	{
		auto toy = BaseToy::create((ToyType)i);

		_toies.pushBack(toy);
		this->addChild(toy);
		toy->setVisible(false);
	}

	return true;
}

void ToyLayer::moveKoala(cocos2d::Vec2 position)
{
    static Vec2 startPos = Vec2(605,182);
    auto resultPos = Vec2(startPos.x+180*position.x,startPos.y+113*position.y);
    _koala->move(resultPos);
	_koala->setDrawerPosition(position);
}

void ToyLayer::checkAnyToyInPosition(Vec2 position)
{
	int index = 0;
	//find if the position in toyPosition variable
	for (auto item : _toyPositions)
	{
		if (item == position)
		{
			break;
		}
		index++;
	}

	if (index != _toyPositions.size())
	{
		//to do,if the position has been found

		//here we find it,put it on screen
		_putOnToies.pushBack(_toies.at(index));
		_koala->moveDownWithGift();
	}
}

void ToyLayer::putOnToy()
{
	auto toy = _putOnToies.back();
	auto index = _putOnToies.size()-1;
	toy->setPosition(_koala->getBodyPosition()+Vec2(50,-50));
	toy->setVisible(true);
	float duration = _putOnPositions.at(index).distance(_koala->getBodyPosition()+Vec2(50,-50))/Toy_Speed;
    toy->runAction(Spawn::create(EaseBackIn::create(MoveTo::create(duration,_putOnPositions.at(index))) ,NULL));
}

void ToyLayer::initPutOnPositions()
{
	auto width = _winSize.width/10;
	auto offset = 20;
	for (int i = 0;i<k_toy_count;i++)
	{
		_putOnPositions.push_back(Vec2(offset+width*(i+1),offset + 70));
	}
}