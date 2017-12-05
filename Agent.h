///class header file for Agent
///author: HU FANGYUAN
///2017.11~
#pragma once
#include <vector>
#include <unordered_map>
#include <tuple>
#include "Log.h"

template <typename Mkt>
class Agent : public Log{
public:
	typedef typename Mkt::Commodity Cmt;
	typedef typename Mkt::Order_t Order_t;
	explicit Agent(const Mkt& m) : mkt(m){}
	~Agent(){}
	
	template <bool IsBid>
	bool deal(const Order_t order){}
	template <>
	bool deal<true>(const Order_t order){
		try{
			holdings[std::get<0>(order)] += std::get<1>(order);
			return true;
		}catch(...){
			return false;
		}
	}
	template <>
	bool deal<false>(const Order_t order){
		try{
			money += std::get<1>(order) * std::get<2>(order);
			return true;
		}catch(...){
			return false;
		}
	}
	bool bid(const Cmt c, int num, int price){
		try{
			return mkt.setBidOrder(this, std::make_tuple(c, num, price));
		}catch(...){
			return false;
		}
	}
	bool ask(const Cmt c, int num, int price){
		try{
			return mkt.setAskOrder(this, std::make_tuple(c, num, price));
		}catch(...){
			return false;
		}
	}
	bool retrieveOrder(){}
	
private:
	Mkt& mkt;
	const std::vector<Cmt> necessities;
	std::unordered_map<Cmt,int> holdings;
	int money;
	int id;
	int life;
};