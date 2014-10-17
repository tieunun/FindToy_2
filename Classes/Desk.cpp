#include "Desk.h"

Desk::Desk()
{

}

Desk::~Desk()
{

}

void Desk::onEnter()
{
	BaseNode::onEnter();
	if (_onEnterCount >1)
	{
		return;
	}
	auto body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("desk"));
	this->addChild(body);
	this->setContentSize(body->getContentSize());
}