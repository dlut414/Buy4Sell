///class header file for Agent
///author: HU FANGYUAN
///2017.11~
#pragma once
#include <vector>
#include <unordered_map>
#include <pair>
#include <tuple>
#include "Log.h"

template <typename Mkt>
class Agent : public Log{
public:
	typedef typename Mkt::Commodity Cmt;
	typedef typename Mkt::Order_t Order_t;
	explicit Agent(const Mkt& m, const std::vector<Cmt>& nec) : mkt(m), necessities(nec){}
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
			const int total = num* price;
			if(money < total) return false;
			if( mkt.setBidOrder(this, Order_t(c, num, price)) ) {
				onOrder.push_back({true, Order_t(c, num, price)});
				money -= total;
				return true;
			}
			else return false;
		}catch(...){
			return false;
		}
	}
	bool ask(const Cmt c, int num, int price){
		try{
			if(!holdings.count(c) || holdings[c] < num) return false;
			if( mkt.setAskOrder(this, Order_t(c, num, price)) ){
				onOrder.push_back({false, Order_t(c, num, price)});
				holdings[c] -= num;
				return true;
			}
			else return false;
		}catch(...){
			return false;
		}
	}
	bool retrieveOrder(){
		
	}
	void update(){
		
	}
	
private:
	Mkt& mkt;
	const std::vector<Cmt> necessities;
	std::vector<std::pair<bool,Order_t>> onOrder; //true for bid
	std::unordered_map<Cmt,int> holdings;
	int money;
	int id;
	int life;
};