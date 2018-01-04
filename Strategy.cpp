///cpp file for Strategy: handle Strategy for each Agent
///author: HU FANGYUAN
///2017.11~
#include "Strategy.hpp"
#include "Agent.hpp"
#include "Market.hpp"

StrategyBase::StrategyBase() {}
StrategyBase::~StrategyBase(){}

Strategy_::Strategy_(){}
Strategy_::~Strategy_(){}
void Strategy_::act(Agent* const agt, Market* const mkt){
	const auto& bidOrder = mkt->getBidOrder();
	std::cout << sizeof(bidOrder) << std::endl;
	return;
}
