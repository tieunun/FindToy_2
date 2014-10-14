#pragma once
#include "BaseLayer.h"
#include "BaseToy.h"
#include "Koala.h"
class ToyLayer :
	public BaseLayer
{
public:
	ToyLayer(void);
	~ToyLayer(void);

	virtual bool init();
private:
	Vector<BaseToy*> toies;
	std::vector<Vec2> toyPositions;
	Koala *koala;
};

