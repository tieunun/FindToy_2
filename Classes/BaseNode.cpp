#include "BaseNode.h"


BaseNode::BaseNode(void)
{
	_onEnterCount = 0;
}


BaseNode::~BaseNode(void)
{
}

void BaseNode::onEnter()
{
	_onEnterCount++;
	Node::onEnter();
}

Rect BaseNode::getRectInGL(Node *node)
{
	auto postion = node->getPosition();
	auto size = node->getContentSize();
	auto parent = this->getParent();
	auto parentPos = parent->getPosition();
	return Rect(postion.x+parentPos.x,postion.y+parentPos.y,size.width,size.height);
}