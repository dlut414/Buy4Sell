///class header file for Strategy: handle Strategy for each Agent
///author: HU FANGYUAN
///2017.11~
#pragma once
#include "Log.h"

class StrategyBase : public Log{
public:
	StrategyBase() {}
	~StrategyBase(){}
	virtual void Act() = 0;
};

class Strategy_ : public StrategyBase{
public:
	Strategy_(){}
	~Strategy_(){}
	void Act(){
		return;
	}

};