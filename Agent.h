///class header file for Agent
///author: HU FANGYUAN
///2017.11~
#pragma once
#include <vector>
#include <unordered_map>

template <typename Market, typename Commodity>
class Agent{
public:
	explicit Agent(const Market& m) : mkt(m){}
	~Agent(){}
	
	void transaction(){}
	int bid(){}
	int ask(){}
	
private:
	Market& mkt;
	const std::vector<Commodity> necessities;
	std::unordered_map<Commodity,int> holdings;
	int life;
};