#pragma once
#include "BaseLayer.h"
#include "BaseToy.h"
class ToyLayer :
	public BaseLayer
{
public:
	ToyLayer(void);
	~ToyLayer(void);

	virtual bool init();
private:
	Vector<BaseToy*> toies;
};

