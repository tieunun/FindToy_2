
#include "BaseScene.h"


	BaseScene::BaseScene(void)
{
}


BaseScene::~BaseScene(void)
{
}

bool BaseScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	return true;
}