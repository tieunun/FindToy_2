#include "Buyer.h"
#include "BaseToy.h"
#define Buyer_Speed 200.0f

Buyer::Buyer()
{
	_buyerType = (BuyerType)-1;
}

Buyer::~Buyer()
{

}

Buyer *Buyer::create(BuyerType type)
{
	auto buyer = new Buyer();
	buyer->init();
	buyer->setBuyerType(type);
	buyer->autorelease();
	return buyer;
}

void Buyer::onEnter()
{
	BaseNode::onEnter();

}

bool Buyer::init()
{
	if (!BaseNode::init())
	{
		return false;
	}

	if (_buyerType <0 || _buyerType >= k_buyer_count)
	{
		_buyerType = (BuyerType)(int)(CCRANDOM_0_1()*(k_buyer_count-1));
	}
	std::string buyers[] = {"monkey","rabbit","sheep","pig"};
	auto frame_name = StringUtils::format("buyer_%s_2.png",buyers[_buyerType].c_str());
	_body = Sprite::createWithSpriteFrameName(frame_name);
	this->addChild(_body);

	_buySign = BuySign::create();
	this->addChild(_buySign);
	_buySign->setVisible(false);
	_buySign->setPosition(20,200);
	return true;
}

void Buyer::buy()
{
	static auto buyPos = Vec2(100,203);
	
	auto animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("buyer_animation_%d",_buyerType));
	_body->runAction(Animate::create(animation));
	auto move = MoveTo::create(this->getPosition().distance(buyPos)/Buyer_Speed,buyPos);
	this->runAction(Sequence::create(move,CallFunc::create([=](){
		_body->stopAllActions();
        std::string buyers[] = {"monkey","rabbit","sheep","pig"};
        auto frame_name = StringUtils::format("buyer_%s_2.png",buyers[_buyerType].c_str());
        _body->setSpriteFrame(frame_name);
		ToyType toy;
		while (true)
		{
			bool buyed = false;
			toy =(ToyType)(int)(CCRANDOM_0_1()*(k_toy_count-1));
			if (_buyedToies.size()==k_toy_count)
			{
				_buyedToies.clear();
			}
			for (auto type : _buyedToies)
			{
				if (type == toy)
				{
					buyed = true;
				}
			}
			if (buyed)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		_buySign->setToy(toy);
		_buyedToies.push_back(toy);
	}),NULL));
}