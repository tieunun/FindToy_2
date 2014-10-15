#include "PlayToyPlayLayer.h"

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

	return true;
}

void PlayToyPlayLayer::setType(ToyType var)
{
	if (!_toy)
	{
		log("Toy is null ,can not be set type");
		return;
	}

	if (var!= _type)
	{
		this->removeChildByTag(_type,true);
		_toy = BaseToy::createBig(_type);
		this->addChild(_toy,0,_type);
	}
}

ToyType PlayToyPlayLayer::getType()
{
	return _type;
}