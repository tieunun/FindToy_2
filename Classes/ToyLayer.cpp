#include "ToyLayer.h"
#include "GameConfigure.h"
#include "Ladder.h"
#include "GameScene.h"
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
	this->addChild(_koala);
	_koala->setPosition(386,182);
    _koala->setOriginPos(_koala->getPosition());
    _koala->setTargetPos(_koala->getPosition());
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
    //static Vec2 startPos = Vec2(605,182);
    //auto resultPos = Vec2(startPos.x+180*position.x,startPos.y+113*position.y);
    _koala->move(position);
}

void ToyLayer::checkAnyToyInPosition(Vec2 position)
{
//	//index is the toy type
//	int index = 0;
//	//find if the position in toyPosition variable
//	for (auto item : _toyPositions)
//	{
//		if (item == position)
//		{
//			break;
//		}
//		index++;
//	}
//
//	_popToy->setPosition(Vec2(349,274)+Vec2(186*position.x,113*position.y));
//	if (index != _toyPositions.size())
//	{
//		//if the position has been found
//		//_popToy->setPosition();
//		_popToy->setVisible(true);
//		_popToy->setOpacity(128);
//		if (_popToy->isPoped(position))
//		{
//			_popToy->popToy((ToyType)-1);
//		}
//		else
//		{	
//			_popToy->popToy((ToyType)index);
//			//here we find it,put it on screen
//			auto scene = (GameScene*)this->getParent();
//			scene->setDrawerShouldTouch(false);
//			this->runAction(Sequence::create(DelayTime::create(2),
//				CallFunc::create([=](){
//					_putOnToies.pushBack(_toies.at(index));
//					//_koala->moveDownWithGift();
//			}),
//				CallFunc::create([=](){
//
//					auto scene = (GameScene*)this->getParent();
//					scene->setDrawerShouldTouch(true);
//			})
//				,NULL
//				));
//		}
//	}
//	else
//	{
//		_popToy->popToy((ToyType)-1);
//	}
}

void ToyLayer::putOnToy()
{
////	auto toy = _putOnToies.back();
////	auto index = _putOnToies.size()-1;
////	//toy->setPosition(_koala->getBodyPosition()+Vec2(50,-50));
////	toy->setVisible(true);
////	//float duration = _putOnPositions.at(index).distance(_koala->getBodyPosition()+Vec2(50,-50))/Toy_Speed;
////    //toy->runAction();
////	//toy->runAction(Sequence::create(Spawn::create(EaseBackIn::create(MoveTo::create(duration,_putOnPositions.at(index))) ,NULL),
////		CallFunc::create([=]()
////	{
////		Director::getInstance()->getEventDispatcher()->setEnabled(true);
////	}),NULL
////		));
}

void ToyLayer::initPutOnPositions()
{
//	auto width = _winSize.width/10;
//	auto offset = 20;
//	for (int i = 0;i<k_toy_count;i++)
//	{
//		_putOnPositions.push_back(Vec2(offset+width*(i+1),offset + 70));
//	}
}
//
void ToyLayer::setShouldDrawerTouched(bool touched)
{
//	auto scene = (GameScene*)this->getParent();
//	scene->setDrawerShouldTouch(touched);
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