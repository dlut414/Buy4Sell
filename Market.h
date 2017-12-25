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
				for(auto i=bidv.rbegin(), j=askv.begin();i!=bidv.rend()&&j!=askv.end();++i,++j){
					if(get<3>(*i) < get<3>(*j)) break;
					auto& nbid = get<2>(*i);
					auto& nask = get<2>(*j);
					const int volume = min(nbid, nask);
					const int price = (get<3>(*i) + get<3>(*j)) / 2;
					b = b && get<1>(*i)->dealBid(get<0>(*i), volume, price);
					a = a && get<1>(*j)->dealAsk(get<0>(*j), volume, price);
					nbid -= volume;
					nask -= volume;
					if(nbid != 0) --i;
					if(nask != 0) --j;
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
	void showBidOrder()const{
		cout << setw(11) << "Commodity" << setw(7) << "Number" << setw(7) << "Price" << endl;
		for(auto it=bidOrder.begin();it!=bidOrder.end();++it){
			for(auto itv=it->second.begin();itv!=it->second.end();++itv){
				cout << setw(10) << it->first << " "
					<< setw(6) << get<2>(itv->second) << " " << setw(6) << get<3>(itv->second) << endl;
			}
		}
	}
	void showBidOrder()const{
		cout << setw(11) << "Commodity" << setw(7) << "Number" << setw(7) << "Price" << endl;
		for(auto it=askOrder.begin();it!=askOrder.end();++it){
			for(auto itv=it->second.begin();itv!=it->second.end();++itv){
				cout << setw(10) << it->first << " "
					<< setw(6) << get<2>(itv->second) << " " << setw(6) << get<3>(itv->second) << endl;
			}
		}
	}
private:
	OrderBook_t bidOrder;
	OrderBook_t askOrder;
};