///class header file for Market: handle market information
///author: HU FANGYUAN
///2017.11~
#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <utility>
#include <tuple>
#include <algorithm>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include "common.hpp"
#include "Log.h"
using namespace std;
using boost::uuids::uuid;
using boost::uuids::random_generator;

class Market : public Log{
public:
	typedef Agent* AgentHandle_t;
	typedef tuple<uuid,AgentHandle_t,int,int> Order_t; //0:uuid, 1:AgentHandle_t, 2:number, 3:price
	typedef unordered_map<int,vector<Order_t>> OrderBook_t; //Commodity -> vector(Order_t)
	explicit Market();
	~Market();
	bool doTransaction();
	bool setBidOrder(const int c, const Order_t& order);
	bool setAskOrder(const int c, const Order_t& order);
	bool retrieveOrder(const int c, const uuid& id);
	const OrderBook_t& getBidOrder()const;
	const OrderBook_t& getAskOrder()const;
	void showBidOrder()const;
	void showAskOrder()const;
private:
	OrderBook_t bidOrder;
	OrderBook_t askOrder;
};