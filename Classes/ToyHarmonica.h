#pragma once
#include "BaseToy.h"
class ToyHarmonica :
	public BaseToy
{
public:
	ToyHarmonica(void);
	~ToyHarmonica(void);

	CREATE_FUNC(ToyHarmonica);
	virtual void onEnter();

	void play() ;
private:
	void onHarmonnicaTouched(Ref *pSender);
};

