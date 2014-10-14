#include "ToyLayer.h"
#include "GameConfigure.h"

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

	for (int i = 0 ;i < k_toy_count;i++)
	{
		auto toy = BaseToy::create((ToyType)i);
		
		toies.pushBack(toy);
		this->addChild(toy);
		toy->setVisible(false);
	}

	toyPositions = GameConfigure::getInstance()->getToyPosition();

	return true;
}