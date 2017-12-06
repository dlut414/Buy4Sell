///class header file for Agent
///author: HU FANGYUAN
///2017.11~
#pragma once
#include <vector>
#include <unordered_map>
#include <pair>
#include <tuple>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include "Log.h"

template <typename Mkt>
class Agent : public Log{
public:
	typedef typename Mkt::Commodity Cmt;
	typedef typename Mkt::Order_t Order_t;
	explicit Agent(const Mkt& m, const std::vector<Cmt>& nec) : mkt(m), necessities(nec){}
	~Agent(){}
	
	bool dealBid(const Order_t order){
		try{
			for(auto it=bidOrder.begin();it!=bidOrder.end();++it){
				if(*it == order) {
					bidOrder.erase(it);
					break;
				}
			}
			holdings[std::get<0>(order)] += std::get<1>(order);
			return true;
		}catch(...){
			return false;
		}
	}
	bool dealAsk(const Order_t order){
		try{
			for(auto it=askOrder.begin();it!=askOrder.end();++it){
				if(*it == order) {
					askOrder.erase(it);
					break;
				}
			}
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
				bidOrder.push_back(Order_t(c, num, price));
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
				askOrder.push_back(Order_t(c, num, price));
				holdings[c] -= num;
				return true;
			}
			else return false;
		}catch(...){
			return false;
		}
	}
	bool retrieveOrder(const size_t i){
		try{

		}catch(...){
			return false;
		}
	}
	void update(){
		
	}
	
private:
	Mkt& mkt;
	const std::vector<Cmt> necessities;
	std::vector<Order_t> bidOrder;
	std::vector<Order_t> askOrder;
	std::unordered_map<Cmt,int> holdings;
	int money;
	int id;
	int life;
};