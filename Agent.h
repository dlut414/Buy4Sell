///class header file for Agent
///author: HU FANGYUAN
///2017.11~
#pragma once
#include <vector>
#include <unordered_map>

template <typename Mkt, typename Cmt>
class Agent{
public:
	explicit Agent(const Mkt& m) : mkt(m){}
	~Agent(){}
	
	void transaction(){}
	int bid(){}
	int ask(){}
	
private:
	Mkt& mkt;
	const std::vector<Cmt> necessities;
	std::unordered_map<Cmt,int> holdings;
	int life;
};