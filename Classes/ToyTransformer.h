#pragma once
#include "BaseToy.h"
class ToyTransformer :
	public BaseToy
{
public:
	ToyTransformer(void);
	~ToyTransformer(void);

	CREATE_FUNC(ToyTransformer);
	virtual void onEnter();
	void play();

private:
};

