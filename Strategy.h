///class header file for Strategy: handle Strategy for each Agent
///author: HU FANGYUAN
///2017.11~
#pragma once
#include "Log.h"

template <typename Mkt>
class StrategyBase : public Log{
public:
	explicity StrategyBase(const Mkt& m) : mkt(m){}
	~StrategyBase(){}
	virtual void Act() = 0;
	const Mkt& mkt;
};

template <typename Agt, typename Mkt>
class Strategy_ : public StrategyBase<Mkt>{
public:
	explicit Strategy_(const Agt& a, const Mkt& m) : agt(a), StrategyBase::mkt(m){}
	~Strategy_(){}
	void Act(){
		return;
	}
private:
	const Agt* agt;
};