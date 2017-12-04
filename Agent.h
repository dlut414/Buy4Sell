///class header file for Agent
///author: HU FANGYUAN
///2017.11~
#pragma once
#include <vector>
#include <unordered_map>

template <typename Mkt>
class Agent{
public:
	typedef Mkt::Commodity Cmt;
	explicit Agent(const Mkt& m) : mkt(m){}
	~Agent(){}
	
	bool transaction(){}
	bool bid(){
		try{
			
		}catch(...){
			return false;
		}
	}
	bool ask(){
		try{
			
		}catch(...){
			return false;
		}
	}
	
private:
	Mkt& mkt;
	const std::vector<Cmt> necessities;
	std::unordered_map<Cmt,int> holdings;
	int life;
};