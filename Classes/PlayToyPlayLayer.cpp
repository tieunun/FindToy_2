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
	layer->autorelease();
	return layer;
}

bool PlayToyPlayLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	switch (_type)
	{
	case k_toy_harmonica:
		break;
	default:
		break;
	}

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