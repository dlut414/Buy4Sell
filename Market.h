///class header file for Market: handle market information
///author: HU FANGYUAN
///2017.11~
#pragma once
#include <vector>
#include <unordered_map>
#include <utility>
#include <tuple>
#include <algorithm>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/functional/hash.hpp>
#include "Log.h"
#include "Agent.h"
using namespace std;
using boost::uuids::uuid;
using boost::uuids::random_generator;

template <typename Commodity, typename Hash = boost::hash<Commodity>>
class Market : public Log{
public:
	typedef Commodity Cmt;
	typedef Agent<Market<Cmt>>* AgentHandle_t;
	typedef tuple<uuid,AgentHandle_t,int,int> Order_t; //0:uuid, 1:AgentHandle_t, 2:number, 3:price
	typedef unordered_map<Cmt,vector<Order_t>,Hash> OrderBook_t; //Commodity -> vector(Order_t)
	explicit Market(){}
	~Market(){}
	bool doTransaction(){
		try{
			bool b = true, a = true;
			for(auto it=bidOrder.begin();it!=bidOrder.end();++it){
				if(!askOrder.count(it->first)) continue;
				auto& bidv = it->second;
				auto& askv = askOrder[it->first];
				if(bidv.empty() || askv.empty()) continue;
				sort(bidv.begin(), bidv.end(), [](auto& p, auto& q){ return get<3>(p) < get<3>(q); });
				sort(askv.begin(), askv.end(), [](auto& p, auto& q){ return get<3>(p) < get<3>(q); });
				for(size_t i=bidv.size()-1, j=0;i>=0&&j<askv.size();i--,j++){
					if(get<3>(bidv[i]) < get<3>(askv[j])) break;
					auto& nbid = get<2>(bidv[i]);
					auto& nask = get<2>(askv[j]);
					const int volume = min(nbid, nask);
					const int price = (get<3>(bidv[i]) + get<3>(askv[j])) / 2;
					b = b && get<1>(bidv[i])->dealBid(get<0>(bidv[i]), price);
					a = a && get<1>(askv[j])->dealAsk(get<0>(askv[j]), price);
					nbid -= volume;
					nask -= volume;
					if(nbid != 0) i++;
					if(nask != 0) j--;
				}
				for(size_t i=0;i<bidv.size();i++){
					if(get<2>(bidv[i]) == 0) {
						bidv.erase(bidv.begin() + i);
						i--;
					}
				}
				for(size_t i=0;i<askv.size();i++){
					if(get<2>(askv[i]) == 0) {
						askv.erase(askv.begin() + i);
						i--;
					}
				}
			}
			return a && b;
		}catch(...){
			return false;
		}
	}
	bool setBidOrder(const Cmt c, const Order_t& order){
		try{
			bidOrder[c].push_back(order);
			return true;
		}catch(...){
			return false;
		}
	}
	bool setAskOrder(const Cmt c, const Order_t& order){
		try{
			askOrder[c].push_back(order);
			return true;
		}catch(...){
			return false;
		}
	}
	bool retrieveOrder(const Cmt c, const uuid& id){
		try{
			auto& bidv = bidOrder[c];
			for(auto it=bidv.begin();it!=bidv.end();++it){
				if(get<0>(*it) == id){
					bidv.erase(it);
					return true;
				}
			}
			auto& askv = askOrder[c];
			for(auto it=askv.begin();it!=askv.end();++it){
				if(get<0>(*it) == id){
					askv.erase(it);
					return true;
				}
			}
			return false;
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