///class header file for Market: handle market information
///author: HU FANGYUAN
///2017.11~
#pragma once
#include <vector>
#include <unordered_map>
#include <pair>

typedef std::pair<int,int> Pii; //nunber -> price

template <typename Commodity>
class Market{
public:
	typedef std::pair<Commodity,Pii> Order_t;
	typedef std::unordered_map<Commodity,std::vector<Pii>> OrderBook_t;
	explicit Market(){}
	~Market(){}
	bool setBidOrder(const Order_t& order){
		try{
			bidOrder[order.first].push_back(order.second);
			return true;
		}catch(...){
			return false;
		}
	}
	bool setAskOrder(const Order_t& order){
		try{
			askOrder[order.first].push_back(order.second);
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