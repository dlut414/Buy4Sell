///class header file for Market: handle market information
///author: HU FANGYUAN
///2017.11~
#pragma once
#include <vector>
#include <unordered_map>
#include <pair>
#include <tuple>
#include <algorithm>
#include "Log.h"
#include "Agent.h"
using namespace std;

template <typename Commodity>
class Market : public Log{
public:
	typedef Commodity Cmt;
	typedef Agent<Market<Cmt>>* AgentHandle_t;
	typedef tuple<Cmt,int,int> Order_t; //Commodity, number, price
	typedef unordered_map<Cmt,vector<tuple<AgentHandle_t,int,int>>> OrderBook_t; //Commodity -> vector(handle, number, price)
	explicit Market(){}
	~Market(){}
	bool doTransaction(){
		try{
			for(auto it=bidOrder.begin();it!=bidOrder.end();++it){
				if(!askOrder.count(it->first)) continue;
				auto& bidv = it->second;
				auto& askv = askOrder[it->first];
				if(bidv.empty() || askv.empty()) continue;
				sort(bidv.begin(), bidv.end(), [](const auto& a, const auto& b){ return get<2>(a) < get<2>(b); });
				sort(askv.begin(), askv.end(), [](const auto& a, const auto& b){ return get<2>(a) < get<2>(b); });
				for(size_t i=bidv.size()-1, j=0;i>=0;j<ask.size();i--,j++){
					if(get<2>(bidv[i]) < get<2>(askv[j])) break;
					auto& nbid = get<1>(bidv[i]);
					auto& nask = get<1>(askv[j]);
					const int volume = min(nbid, nask);
					const int price = (get<2>(bidv[i]) + get<2>(askv[j])) / 2;
					bool b = get<0>(bidv[i])->deal<true>(make_tuple(it->first, volume, price));
					bool a = get<0>(askv[j])->deal<false>(make_tuple(it->first, volume, price));
					nbid -= volume;
					nask -= volume;
					if(nbid != 0) i++;
					if(nask != 0) j--;
				}
				for(size_t i=0;i<bidv.size();i++){
					if(get<1>(bidv[i]) == 0) {
						bidv.erase(bidv.begin() + i);
						i--;
					}
				}
				for(size_t i=0;i<askv.size();i++){
					if(get<1>(askv[i]) == 0) {
						askv.erase(askv.begin() + i);
						i--;
					}
				}
				return a && b;
			}
		}catch(...){
			return false;
		}
	}
	bool setBidOrder(const AgentHandle_t ah, const Order_t& order){
		try{
			bidOrder[get<0>(order)].push_back(make_tuple(ah,get<1>(order),get<2>(order)));
			return true;
		}catch(...){
			return false;
		}
	}
	bool setAskOrder(const AgentHandle_t ah, const Order_t& order){
		try{
			askOrder[get<0>(order)].push_back(make_tuple(ah,get<1>(order),get<2>(order)));
			return true;
		}catch(...){
			return false;
		}
	}
	bool retrieveOrder(const AgentHandle_t ah, const Order_t& order){
		
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