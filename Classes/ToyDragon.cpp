#include "ToyDragon.h"
#define Toy_Dragon_Speed 300

ToyDragon::ToyDragon()
{
	_type = ToyType::k_toy_frog;
}

ToyDragon::~ToyDragon()
{

}

void ToyDragon::onEnter()
{
	BaseNode::onEnter();

	_body = Sprite::create();
	this->addChild(_body);
	auto animation = AnimationCache::getInstance()->getAnimation("toy_dragon_animation_fly");
	_body->runAction(Animate::create(animation));

	_eruption = DragonEruption::create();
	_eruption->setPosition(-281,-33);
	this->addChild(_eruption);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ToyDragon::onDragonTouched,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}

void ToyDragon::play()
{

}

bool ToyDragon::onDragonTouched(Touch *touch,Event *event)
{
	auto location = this->convertTouchToNodeSpace(touch);
	if (!_body->getBoundingBox().containsPoint(location))
	{
		this->stopActionByTag(103);
		auto distance = location;
		if (distance.x<0)
		{
			this->setDragonFlipped(false);
		}
		else
		{
			this->setDragonFlipped(true);
		}
		auto offset = _body->isFlippedX()?-281:281;
		auto move1 = MoveBy::create(distance.distance(Vec2(-offset,0))/Toy_Dragon_Speed,Vec2(distance.x+offset,distance.y));
		move1->setTag(103);
// 		this->runAction(Sequence::create(CallFunc::create([=]{
// 			_toyAnimate = true;
// 		})))
		

		//auto targetAciton = TargetedAction::create(_eruption,Animate::create(animation));
		auto action = this->runAction(Sequence::create(move1,
			CallFunc::create([=]{
				_eruption->play();
		})
			,NULL));
		action->setTag(103);
	}
	return true;
}

void ToyDragon::setDragonFlipped(bool flipped)
{
	_body->setFlippedX(flipped);
	_eruption->setEruptionFlipped(flipped);
	_eruption->setPositionX(flipped?281:-281);
}