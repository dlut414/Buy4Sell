///class header file for Market: handle market information
///author: HU FANGYUAN
///2017.11~
#pragma once
#include <vector>
#include <unordered_map>
#include <pair>
#include <tuple>
#include "Agent.h"
using namespace std;

template <typename Commodity>
class Market{
public:
	typedef Commodity Cmt;
	typedef Agent<Market<Cmt>>* AgentHandle_t;
	typedef tuple<Cmt,AgentHandle_t,int,int> Order_t; //Commodity, AgentHandle, number, price
	typedef unordered_map<Cmt,vector<tuple<AgentHandle_t,int,int>>> OrderBook_t;
	explicit Market(){}
	~Market(){}
	bool doTransaction(){
		try{
			
		}catch(...){
			return false;
		}
	}
	bool setBidOrder(const Order_t& order){
		try{
			bidOrder[get<0>(order)].push_back(make_tuple(get<1>(order),get<2>(order),get<3>(order)));
			return true;
		}catch(...){
			return false;
		}
	}
	bool setAskOrder(const Order_t& order){
		try{
			askOrder[get<0>(order)].push_back(make_tuple(get<1>(order),get<2>(order),get<3>(order)));
			return true;
		}catch(...){
			return false;
		}
	}
	const OrderBook_t& getBidOrder()const{
		return bidOrder;
	}
	const OrderBook_t& getAskOrder()const{
		return askOrder;
	}
private:
	OrderBook_t bidOrder;
	OrderBook_t askOrder;
};