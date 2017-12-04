///class header file for Agent
///author: HU FANGYUAN
///2017.11~
#pragma once
#include <vector>
#include <unordered_map>

template <typename Mkt>
class Agent{
public:
	typedef typename Mkt::Commodity Cmt;
	typedef typename Mkt::Order_t Order_t;
	explicit Agent(const Mkt& m) : mkt(m){}
	~Agent(){}
	
	bool bid(const Cmt c, int num, int price){
		try{
			return mkt.setBidOrder({c, {num, price}});
		}catch(...){
			return false;
		}
	}
	bool ask(const Cmt c, int num, int price){
		try{
			return mkt.setAskOrder({c, {num, price}});
		}catch(...){
			return false;
		}
	}
	bool retrieveOrder(){}
	
private:
	Mkt& mkt;
	const std::vector<Cmt> necessities;
	std::unordered_map<Cmt,int> holdings;
	int id;
	int life;
};