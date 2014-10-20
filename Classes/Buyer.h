#pragma once
#include "BaseNode.h"
#include "BuySign.h"

typedef enum BuyerType
{
	k_buyer_monkey,
	k_buyer_rabbit,
	k_buyer_sheep,
	k_buyer_pig,
	k_buyer_count
}BuyerType;
class Buyer:public BaseNode
{
public:
	Buyer();
	~Buyer();
	virtual void onEnter();
	virtual bool init();
	CREATE_FUNC(Buyer);
	static Buyer *create(BuyerType type);
	CC_SYNTHESIZE(Sprite*,_body,Body);
	CC_SYNTHESIZE(BuyerType,_buyerType,BuyerType);
    CC_SYNTHESIZE(BuySign*, _buySign, BuySign);

	void buy();
	void leave();
private:
	std::vector<ToyType> _buyedToies;
};