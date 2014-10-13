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

	auto body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("desk"));
	this->addChild(body);
	this->setContentSize(body->getContentSize());
}