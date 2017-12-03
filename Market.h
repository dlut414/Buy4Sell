///class header file for Market: handle market information
///author: HU FANGYUAN
///2017.11~
#pragma once
#include <vector>
#include <unordered_map>
#include <pair>

enum Commodity {};
typedef std::pair<int,int> Pii; //nunber -> price
typedef std::pair<Commodity,Pii> Order_t;

class Market{
public:
	typedef std::unordered_map<Commodity,std::vector<Pii>> OrderBook_t;
	Market(){}
	~Market(){}
	bool setBidOrder(const Order_t& order){
		bidOrder[order.first].push_back(order.second);
	}
	bool setAskOrder(const Order_t& order){
		askOrder[order.first].push_back(order.second);
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