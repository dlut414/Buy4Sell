///class header file for Strategy: handle Strategy for each Agent
///author: HU FANGYUAN
///2017.11~
#pragma once
#include "common.hpp"
#include "Log.hpp"

class StrategyBase : public Log{
public:
	StrategyBase();
	~StrategyBase();
	virtual void act(Agent* const, Market* const) = 0;
};

class Strategy_ : public StrategyBase{
public:
	Strategy_();
	~Strategy_();
	void act(Agent* const agt, Market* const mkt);
};
