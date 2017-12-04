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
	typedef Mkt::Order_t Order_t;
	explicit Agent(const Mkt& m) : mkt(m){}
	~Agent(){}
	
	bool transaction(){}
	bool bid(const Cmt c, int num, int price){
		try{
			mkt.setBidOrder({c, {num, price}});
		}catch(...){
			return false;
		}
	}
	bool ask(const Cmt c, int num, int price){
		try{
			mkt.setAskOrder({c, {num, price}});
		}catch(...){
			return false;
		}
	}
	bool retrieveOrder(){}
	
private:
	Mkt& mkt;
	const std::vector<Cmt> necessities;
	std::unordered_map<Cmt,int> holdings;
	int life;
};