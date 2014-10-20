#include "PlayToyPlayLayer.h"
#include "ClothShelf.h"
#include "ToyDoll.h"
#include "ToyHelicopter.h"
#include "PlayToyScene.h"
#include "ToyDragon.h"

PlayToyPlayLayer::PlayToyPlayLayer()
{

}

PlayToyPlayLayer::~PlayToyPlayLayer()
{

}

PlayToyPlayLayer *PlayToyPlayLayer::create(ToyType toyType)
{
	auto layer = new PlayToyPlayLayer();
	layer->_type = toyType;
	layer->init();
	layer->autorelease();
	return layer;
}

bool PlayToyPlayLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	_toy = BaseToy::createBig(_type);
	this->addChild(_toy);
	_toy->setPosition(_winSize/2);

	switch (_type)
	{
	case k_toy_doll:
		{
			auto clotheShelf = ClothShelf::create();
			clotheShelf->setPosition(317,331);
			this->addChild(clotheShelf);

			_toy->setPosition(987,381);
		}
		break;
	case k_toy_helicopter:
		_toy->setPosition(209,489);
        for ( int i = 0;i<12;i++)
        {
            auto rect_name = StringUtils::format("toy_helicopter_rect_%d",i);
            _rects.push_back(GAME_DATA_RECT(rect_name));
  
        }
		this->scheduleUpdate();
		break;
	case k_toy_chick:
		_toy->setPosition(982,237);
		break;
	default:
		break;
	}

	return true;
}


// void PlayToyPlayLayer::setType(ToyType var)
// {
// 	if (!_toy)
// 	{
// 		log("Toy is null ,can not be set type");
// 		return;
// 	}
// 
// 	if (var!= _type)
// 	{
// 		this->removeChildByTag(_type,true);
// 		_toy = BaseToy::createBig(_type);
// 		this->addChild(_toy,0,_type);
// 	}
// }
// 
// ToyType PlayToyPlayLayer::getType()
// {
// 	return _type;
// }

void PlayToyPlayLayer::changeCloth(int index)
{
	auto toy = (ToyDoll*)_toy;
	toy->changeCloth(index);
}

void PlayToyPlayLayer::changeHair(int index)
{
	auto toy = (ToyDoll*)_toy;
	toy->changeHair(index);
}

void PlayToyPlayLayer::update(float dt)
{
	if (_toy->isVisible()&&_toy->getToyAnimate())
	{
		for (auto rect :_rects)
		{
            if (rect.intersectsRect(Rect(_toy->getPositionX()-48,-68+_toy->getPositionY(), 182,136))) {
                auto toy = (ToyHelicopter*)_toy;
                toy->explode();
                auto scene = (PlayToyScene*)this->getParent();
                scene->stopBackgroundMove();
                this->unscheduleUpdate();
            }   
        }
	}
}

void PlayToyPlayLayer::onHelicopterReachCenter()
{
	auto scene = (PlayToyScene*)this->getParent();
	scene->moveBackground();
}

void PlayToyPlayLayer::moveHelicopter()
{
	auto move = MoveBy::create(_winSize.width/4*3/Toy_Helicopter_H_Speed,Vec2(_winSize.width/4*3,0));
	move->setTag(102);
	_toy->runAction(Sequence::create(move,CallFunc::create([=](){
		_toy->stopActionByTag(102);
	}),NULL));
}

void PlayToyPlayLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(PlayToyPlayLayer::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
   }

void PlayToyPlayLayer::onDraw(const cocos2d::Mat4 &transform, bool transformUpdated)
{
    Director* director = Director::getInstance();
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    glLineWidth( 2.0f );
    DrawPrimitives::setDrawColor4B(255,0,0,255);
    
    //DrawPrimitives::drawRect(_toy->getPosition()+Vec2(-48,-68), _toy->getPosition()+Vec2(125,68));

    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}