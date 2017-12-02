///class header file for Agent
///author: HU FANGYUAN
///2017.11~
#pragma once

template <typename Market>
class Agent{
public:
	explicit Agent(const Market& m) : mkt(m){}
	~Agent(){}
	
	void transaction(){}
	int bid(){}
	int ask(){}
	
private:
	Market& mkt;
}