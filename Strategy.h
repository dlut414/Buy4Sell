///class header file for Strategy: handle Strategy for each Agent
///author: HU FANGYUAN
///2017.11~
#pragma once
#include "Log.h"
#include "Market.h"

template <typename Mkt>
class Strategy : public Log{
public:
	explicit Strategy(const Mkt& m) : mkt(m){}
	~Strategy(){}
private:
	const Mkt& mkt;
};